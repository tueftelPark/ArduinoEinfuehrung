// Arduino Übungseditor — tüftelPark
(function () {
    'use strict';

    document.addEventListener('DOMContentLoaded', function () {
        var exercises = (typeof EXERCISES_DATA !== 'undefined') ? EXERCISES_DATA : [];
        var STORAGE_PREFIX = 'tueftelpark-arduino:';
        var LAST_TAB_KEY = 'tueftelpark-arduino:last-tab';
        var LAST_ACTIVITY_KEY = 'tueftelpark-arduino:last-activity';
        var MAX_AGE_MS = 3 * 60 * 60 * 1000; // 3 Stunden - danach gilt der Stand als "alte Klasse" und wird verworfen

        var currentIndex = 0;
        var currentEx = null;
        var state = {};
        var memoryCache = {};
        var lastCheckPassed = false;
        var fieldRegistry = [];

        var $tabsList = document.getElementById('tabs-list');
        var $exTitle = document.getElementById('ex-title');
        var $exGoal = document.getElementById('ex-goal');
        var $commandsList = document.getElementById('commands-list');
        var $toggleCommandsButton = document.getElementById('toggle-commands-button');
        var $topCard = document.getElementById('top-card');
        var $topBlock = document.getElementById('top-block');
        var $setupBlock = document.getElementById('setup-block');
        var $loopBlock = document.getElementById('loop-block');
        var $checkResult = document.getElementById('check-result');
        var $progress = document.getElementById('task-progress');
        var $codeSections = document.getElementById('code-sections');
        var $chatgptCard = document.getElementById('chatgpt-card');
        var $chatgptPromptBox = document.getElementById('chatgpt-prompt-box');
        var $componentsList = document.getElementById('components-list');
        var $copyButton = document.getElementById('copy-button');

        function segKey(section, idx) { return section + ':' + idx; }
        function stateKey(exId) { return STORAGE_PREFIX + exId; }

        function loadStateFor(exId) {
            if (memoryCache[exId]) return memoryCache[exId];
            var st = {};
            try {
                st = JSON.parse(localStorage.getItem(stateKey(exId)) || '{}');
            } catch (e) { /* localStorage evtl. nicht verfügbar - dann eben nur diese Sitzung */ }
            memoryCache[exId] = st;
            return st;
        }

        function saveStateFor(exId, st) {
            memoryCache[exId] = st;
            try {
                localStorage.setItem(stateKey(exId), JSON.stringify(st));
                localStorage.setItem(LAST_ACTIVITY_KEY, String(Date.now()));
            } catch (e) { /* ignore */ }
        }

        // Löscht den gespeicherten Stand aller Übungen (z.B. für eine neue Klasse)
        function resetAllExercises() {
            memoryCache = {};
            exercises.forEach(function (ex) {
                try { localStorage.removeItem(stateKey(ex.id)); } catch (e) { /* ignore */ }
            });
            try {
                localStorage.removeItem(LAST_ACTIVITY_KEY);
                localStorage.removeItem(LAST_TAB_KEY);
            } catch (e) { /* ignore */ }
        }

        // Wenn seit über 3h nichts mehr gespeichert wurde, gilt der Stand als "alte Klasse" -> automatisch löschen
        function clearIfExpired() {
            var last = null;
            try { last = parseInt(localStorage.getItem(LAST_ACTIVITY_KEY), 10); } catch (e) { /* ignore */ }
            if (last && !isNaN(last) && (Date.now() - last) > MAX_AGE_MS) {
                resetAllExercises();
                return true;
            }
            return false;
        }

        function persist() {
            saveStateFor(currentEx.id, state);
        }

        function escapeHtml(s) {
            return String(s)
                .replace(/&/g, '&amp;')
                .replace(/</g, '&lt;')
                .replace(/>/g, '&gt;');
        }

        // ---------- Aufgaben zählen ----------
        function countTasks(ex, st) {
            var allSet = {};
            var doneSet = {};
            ['top', 'setup', 'loop'].forEach(function (section) {
                (ex[section] || []).forEach(function (seg, idx) {
                    if (seg.type === 'gap' || seg.type === 'inline_gap' || seg.type === 'inline_choice') {
                        allSet[seg.task] = true;
                        var val = st[segKey(section, idx)];
                        var result = validateField(seg, val || '');
                        if (result.status === 'ok') doneSet[seg.task] = true;
                    }
                });
            });
            return { done: Object.keys(doneSet).length, total: Object.keys(allSet).length };
        }

        function isExerciseComplete(ex) {
            if (ex.kind === 'chatgpt') return false;
            var st = loadStateFor(ex.id);
            var c = countTasks(ex, st);
            return c.total > 0 && c.done === c.total;
        }

        function updateProgress() {
            if (currentEx.kind === 'chatgpt') {
                $progress.textContent = 'Zusatzaufgabe';
            } else {
                var c = countTasks(currentEx, state);
                $progress.textContent = c.done + ' / ' + c.total + ' Aufgaben';
            }
            renderTabs();
        }

        // ---------- Tabs ----------
        function renderTabs() {
            $tabsList.innerHTML = '';
            exercises.forEach(function (ex, i) {
                var $btn = document.createElement('button');
                $btn.className = 'tab-button' + (i === currentIndex ? ' active' : '');
                var label = ex.kind === 'chatgpt' ? ('Zusatz: ' + ex.title) : ((i + 1) + '. ' + ex.title);
                $btn.textContent = label;
                if (isExerciseComplete(ex)) {
                    var $chk = document.createElement('span');
                    $chk.className = 'tab-check';
                    $chk.textContent = '✓';
                    $btn.appendChild($chk);
                }
                $btn.addEventListener('click', function () { selectExercise(i); });
                $tabsList.appendChild($btn);
            });
        }

        function selectExercise(i) {
            currentIndex = i;
            currentEx = exercises[i];
            state = loadStateFor(currentEx.id);
            lastCheckPassed = false;
            try { localStorage.setItem(LAST_TAB_KEY, String(i)); } catch (e) { /* ignore */ }
            renderExercise();
        }

        function renderComponentsList(components) {
            $componentsList.innerHTML = '';
            components.forEach(function (c) {
                var card = document.createElement('div');
                card.className = 'component-card';
                var name = document.createElement('div');
                name.className = 'name';
                name.textContent = c.name;
                var desc = document.createElement('div');
                desc.className = 'desc';
                desc.textContent = c.desc;
                card.appendChild(name);
                card.appendChild(desc);
                if (c.idea) {
                    var idea = document.createElement('div');
                    idea.className = 'idea';
                    idea.textContent = c.idea;
                    card.appendChild(idea);
                }
                $componentsList.appendChild(card);
            });
        }

        function renderCombos(combos) {
            var $list = document.getElementById('combos-list');
            $list.innerHTML = '';
            (combos || []).forEach(function (text) {
                var li = document.createElement('li');
                li.textContent = text;
                $list.appendChild(li);
            });
        }

        // ---------- Aufgabe rendern ----------
        function renderExercise() {
            $exTitle.textContent = currentEx.kind === 'chatgpt' ? currentEx.title : ((currentIndex + 1) + '. ' + currentEx.title);
            $exGoal.textContent = currentEx.goal;

            if (currentEx.kind === 'chatgpt') {
                $codeSections.hidden = true;
                $chatgptCard.hidden = false;
                $toggleCommandsButton.hidden = true;
                $commandsList.hidden = true;
                $chatgptPromptBox.value = currentEx.prompt;
                renderComponentsList(currentEx.components || []);
                renderCombos(currentEx.combos || []);
                updateProgress();
                return;
            }

            $codeSections.hidden = false;
            $chatgptCard.hidden = true;
            $toggleCommandsButton.hidden = false;

            $commandsList.innerHTML = '';
            (currentEx.commands || []).forEach(function (c) {
                var row = document.createElement('div');
                row.className = 'command-row';
                var code = document.createElement('code');
                code.textContent = c.code;
                var span = document.createElement('span');
                span.textContent = c.explain;
                row.appendChild(code);
                row.appendChild(span);
                $commandsList.appendChild(row);
            });
            $commandsList.hidden = true;
            $toggleCommandsButton.textContent = '📖 Befehle anzeigen';

            if (currentEx.top && currentEx.top.length) {
                $topCard.classList.add('has-content');
            } else {
                $topCard.classList.remove('has-content');
            }

            fieldRegistry = [];
            renderBlock('top', currentEx.top || [], $topBlock);
            renderBlock('setup', currentEx.setup || [], $setupBlock);
            renderBlock('loop', currentEx.loop || [], $loopBlock);

            $checkResult.hidden = true;
            setCopyLocked(true);
            renderTabs();
            updateProgress();
        }

        function sizeInlineInput($input) {
            var len = Math.max(($input.value || '').length, ($input.placeholder || '').length, 2);
            $input.style.width = (len + 1.5) + 'ch';
        }

        function autoResizeTextarea($ta) {
            var lines = ($ta.value.match(/\n/g) || []).length + 1;
            $ta.rows = Math.max(2, Math.min(lines + 1, 10));
        }

        function renderBlock(section, segments, container) {
            container.innerHTML = '';
            segments.forEach(function (seg, idx) {
                var key = segKey(section, idx);

                if (seg.type === 'fixed') {
                    var span = document.createElement('span');
                    span.className = (seg.kind === 'comment') ? 'code-comment' : 'code-fixed';
                    span.textContent = seg.code;
                    container.appendChild(span);

                } else if (seg.type === 'info') {
                    var info = document.createElement('span');
                    info.className = 'info-box';
                    info.innerHTML = '💡 ' + escapeHtml(seg.hint);
                    container.appendChild(info);

                } else if (seg.type === 'label') {
                    var lab = document.createElement('span');
                    lab.className = 'task-label';
                    lab.innerHTML = '<b>Aufgabe ' + seg.task + ':</b> ' + escapeHtml(seg.hint);
                    container.appendChild(lab);

                } else if (seg.type === 'gap') {
                    var wrap = document.createElement('span');
                    wrap.className = 'task-gap-wrap';
                    var label = document.createElement('span');
                    label.className = 'task-label';
                    label.innerHTML = '<b>Aufgabe ' + seg.task + ':</b> ' + escapeHtml(seg.hint);
                    wrap.appendChild(label);

                    var ta = document.createElement('textarea');
                    ta.className = 'task-gap';
                    ta.placeholder = '// dein Code hier...';
                    ta.value = state[key] || '';
                    if (ta.value.trim()) ta.classList.add('filled');
                    ta.addEventListener('input', function () {
                        state[key] = ta.value;
                        ta.classList.toggle('filled', ta.value.trim().length > 0);
                        ta.classList.remove('field-ok', 'field-error');
                        autoResizeTextarea(ta);
                        persist();
                        updateProgress();
                        setCopyLocked(true);
                    });
                    wrap.appendChild(ta);
                    container.appendChild(wrap);
                    autoResizeTextarea(ta);
                    fieldRegistry.push({ el: ta, seg: seg, section: section, idx: idx, key: key });

                } else if (seg.type === 'inline_gap') {
                    var input = document.createElement('input');
                    input.type = 'text';
                    input.className = 'inline-gap';
                    input.placeholder = seg.placeholder;
                    input.setAttribute('data-task', seg.task);
                    input.title = 'Aufgabe ' + seg.task;
                    input.value = state[key] || '';
                    if (input.value.trim()) input.classList.add('filled');
                    input.addEventListener('input', function () {
                        state[key] = input.value;
                        input.classList.toggle('filled', input.value.trim().length > 0);
                        input.classList.remove('field-ok', 'field-error');
                        sizeInlineInput(input);
                        persist();
                        updateProgress();
                        setCopyLocked(true);
                    });
                    container.appendChild(input);
                    sizeInlineInput(input);
                    fieldRegistry.push({ el: input, seg: seg, section: section, idx: idx, key: key });

                } else if (seg.type === 'inline_choice') {
                    var select = document.createElement('select');
                    select.className = 'inline-choice';
                    select.title = 'Aufgabe ' + seg.task;
                    var optDefault = document.createElement('option');
                    optDefault.value = '';
                    optDefault.textContent = 'wählen…';
                    select.appendChild(optDefault);
                    seg.options.forEach(function (o) {
                        var opt = document.createElement('option');
                        opt.value = o;
                        opt.textContent = o;
                        select.appendChild(opt);
                    });
                    select.value = state[key] || '';
                    if (select.value) select.classList.add('filled');
                    select.addEventListener('change', function () {
                        state[key] = select.value;
                        select.classList.toggle('filled', !!select.value);
                        select.classList.remove('field-ok', 'field-error');
                        persist();
                        updateProgress();
                        setCopyLocked(true);
                    });
                    container.appendChild(select);
                    fieldRegistry.push({ el: select, seg: seg, section: section, idx: idx, key: key });
                }
            });
        }

        // ---------- Code zusammensetzen ----------
        function segmentsToCode(section, segments) {
            var out = '';
            segments.forEach(function (seg, idx) {
                var key = segKey(section, idx);
                if (seg.type === 'fixed') {
                    out += seg.code;
                } else if (seg.type === 'gap') {
                    var v = (state[key] || '').trim();
                    out += v ? (v + '\n') : '';
                } else if (seg.type === 'inline_gap') {
                    var v2 = (state[key] || '').trim();
                    out += v2 ? v2 : seg.placeholder;
                } else if (seg.type === 'inline_choice') {
                    var v3 = state[key] || '';
                    out += v3 ? v3 : seg.options.join(' oder ');
                }
                // 'label' und 'info' Segmente tragen keinen Code bei
            });
            return out;
        }

        function assembleFullCode(ex) {
            var code = '';
            if (ex.lead) code += ex.lead + (ex.lead.slice(-1) === '\n' ? '' : '\n');
            if (ex.raw_header) code += ex.raw_header + '\n\n';
            var top = segmentsToCode('top', ex.top || []);
            if (top.trim()) code += top + '\n\n';
            code += 'void setup()\n{\n' + segmentsToCode('setup', ex.setup || []) + '\n}\n\n';
            code += 'void loop()\n{\n' + segmentsToCode('loop', ex.loop || []) + '\n}\n';
            return code;
        }

        // ---------- Echte Code-Prüfung ----------
        // Bekannte Arduino-Wörter mit korrekter Gross-/Kleinschreibung (Kleinbuchstaben -> richtige Schreibweise)
        var KNOWN_WORDS = {
            'pinmode': 'pinMode', 'digitalwrite': 'digitalWrite', 'digitalread': 'digitalRead',
            'analogread': 'analogRead', 'analogwrite': 'analogWrite', 'delay': 'delay',
            'high': 'HIGH', 'low': 'LOW', 'output': 'OUTPUT', 'input': 'INPUT',
            'serial': 'Serial', 'println': 'println', 'print': 'print', 'begin': 'begin',
            'oled': 'Oled', 'setcursor': 'setCursor', 'setflipmode': 'setFlipMode',
            'setfont': 'setFont', 'clear': 'clear', 'refreshdisplay': 'refreshDisplay',
            'void': 'void', 'setup': 'setup', 'loop': 'loop', 'int': 'int'
        };

        function checkBalance(code) {
            var pairs = { '(': ')', '{': '}', '[': ']' };
            var stack = [];
            var quoteCount = 0;
            for (var i = 0; i < code.length; i++) {
                var c = code[i];
                if (c === '"' && code[i - 1] !== '\\') quoteCount++;
                if (c === '(' || c === '{' || c === '[') {
                    stack.push(c);
                } else if (c === ')' || c === '}' || c === ']') {
                    var open = stack.pop();
                    if (!open || pairs[open] !== c) {
                        return { ok: false, reason: 'Die Klammern passen nicht zusammen (ein "' + c + '" hat kein passendes Gegenstück).' };
                    }
                }
            }
            if (stack.length) {
                return { ok: false, reason: 'Es fehlt noch eine schliessende Klammer für: ' + stack.map(function (o) { return '"' + o + '"'; }).join(', ') + '.' };
            }
            if (quoteCount % 2 !== 0) {
                return { ok: false, reason: 'Ein Anführungszeichen " scheint nicht geschlossen zu sein.' };
            }
            return { ok: true };
        }

        // Entfernt Zeilenkommentare (//...) aus jeder Zeile eines Textes
        function stripLineComments(text) {
            return text.split('\n').map(function (line) {
                var idx = line.indexOf('//');
                return idx === -1 ? line : line.slice(0, idx);
            }).join(' ');
        }

        // Erkennt den häufigen Fehler: ein Punkt (.) wurde als Trenner zwischen Klammer-Argumenten benutzt statt einem Komma (,)
        function hasPeriodInsteadOfComma(raw) {
            var parenRe = /\(([^()]*)\)/g;
            var m;
            while ((m = parenRe.exec(raw))) {
                if (/[A-Za-z0-9_\)]\s*\.\s+[A-Za-z]/.test(m[1])) {
                    return true;
                }
            }
            return false;
        }

        function findCasingIssue(text) {
            var re = /[A-Za-z_][A-Za-z0-9_]*/g;
            var m;
            while ((m = re.exec(text))) {
                var word = m[0];
                var lower = word.toLowerCase();
                if (Object.prototype.hasOwnProperty.call(KNOWN_WORDS, lower) && KNOWN_WORDS[lower] !== word) {
                    return '"' + word + '" - achte auf Gross- und Kleinschreibung.';
                }
            }
            return null;
        }

        // Prüft ein einzelnes Feld und gibt { status: 'empty'|'ok'|'error', message } zurück.
        function validateField(seg, rawValue) {
            var trimmed = (rawValue || '').trim();
            if (!trimmed) return { status: 'empty' };

            if (seg.type === 'gap') {
                if (hasPeriodInsteadOfComma(rawValue)) {
                    return { status: 'error', message: 'Aufgabe ' + seg.task + ': Meinst du dort ein Komma ( , ) statt einem Punkt ( . )?' };
                }
                var cleaned = stripLineComments(rawValue).replace(/\s+/g, ' ').trim();
                if (!cleaned) return { status: 'empty' };

                if (!seg.expect) return { status: 'ok' };

                var re = new RegExp(seg.expect);
                if (re.test(cleaned)) return { status: 'ok' };

                if (!/;\s*$/.test(cleaned)) {
                    return { status: 'error', message: 'Aufgabe ' + seg.task + ': Fehlt am Ende ein Semikolon ( ; )?' };
                }
                var casing = findCasingIssue(cleaned);
                if (casing) {
                    return { status: 'error', message: 'Aufgabe ' + seg.task + ': ' + casing };
                }
                return { status: 'error', message: 'Aufgabe ' + seg.task + ': Das ist noch nicht der richtige Befehl. Schau dir die Aufgabe nochmal an.' };
            }

            // inline_gap / inline_choice
            if (!seg.expect) return { status: 'ok' };
            var re2 = new RegExp(seg.expect);
            if (re2.test(trimmed)) return { status: 'ok' };
            var casing2 = findCasingIssue(trimmed);
            if (casing2) {
                return { status: 'error', message: 'Aufgabe ' + seg.task + ': ' + casing2 };
            }
            return { status: 'error', message: 'Aufgabe ' + seg.task + ': Das passt noch nicht ganz.' };
        }

        function runCheck() {
            if (currentEx.kind === 'chatgpt') return;

            var messages = [];
            var seenTasks = {};
            var incompleteTasks = {};
            var allOk = true;

            fieldRegistry.forEach(function (f) {
                var raw = state[f.key] || '';
                var result = validateField(f.seg, raw);
                f.el.classList.remove('field-ok', 'field-error');
                if (result.status === 'empty') {
                    allOk = false;
                    incompleteTasks[f.seg.task] = true;
                } else if (result.status === 'ok') {
                    f.el.classList.add('field-ok');
                } else {
                    f.el.classList.add('field-error');
                    allOk = false;
                    if (!seenTasks[result.message]) {
                        seenTasks[result.message] = true;
                        messages.push(result.message);
                    }
                }
            });

            var code = assembleFullCode(currentEx);
            var balance = checkBalance(code);
            if (!balance.ok) allOk = false;

            $checkResult.hidden = false;
            var html = '';
            if (allOk) {
                $checkResult.className = 'check-result ok';
                html = '<h4>✅ Sieht gut aus!</h4>' +
                    '<p>Alle Aufgaben sind richtig gelöst. Du kannst den Code jetzt kopieren. ' +
                    'Lade ihn danach in die Arduino IDE hoch, um ihn wirklich zu testen.</p>';
            } else {
                $checkResult.className = 'check-result warn';
                html = '<h4>🔍 Noch nicht ganz fertig</h4><ul>';
                var incompleteList = Object.keys(incompleteTasks).map(Number).sort(function (a, b) { return a - b; });
                if (incompleteList.length) {
                    html += '<li>Noch offene Aufgabe' + (incompleteList.length > 1 ? 'n' : '') + ': <b>' + incompleteList.join(', ') + '</b></li>';
                }
                messages.forEach(function (m) { html += '<li>' + escapeHtml(m) + '</li>'; });
                if (!balance.ok) {
                    html += '<li>' + escapeHtml(balance.reason) + '</li>';
                }
                html += '</ul><p><small>Die rot markierten Kästen im Code oben zeigen dir genau, wo noch ein Fehler ist. Erst wenn alles grün ist, kannst du kopieren.</small></p>';
            }
            $checkResult.innerHTML = html;

            lastCheckPassed = allOk;
            setCopyLocked(!allOk);
        }

        function setCopyLocked(locked) {
            if (currentEx && currentEx.kind === 'chatgpt') return;
            $copyButton.classList.toggle('locked', locked);
        }

        // ---------- Kopieren ----------
        function fallbackCopy(text) {
            var ta = document.createElement('textarea');
            ta.value = text;
            ta.style.position = 'fixed';
            ta.style.opacity = '0';
            document.body.appendChild(ta);
            ta.focus();
            ta.select();
            try { document.execCommand('copy'); } catch (e) { /* ignore */ }
            document.body.removeChild(ta);
        }

        function copyToClipboard(text) {
            if (navigator.clipboard && navigator.clipboard.writeText) {
                navigator.clipboard.writeText(text).catch(function () { fallbackCopy(text); });
            } else {
                fallbackCopy(text);
            }
        }

        function showToast(msg) {
            var $toast = document.getElementById('toast');
            if (!$toast) {
                $toast = document.createElement('div');
                $toast.id = 'toast';
                document.body.appendChild($toast);
            }
            $toast.textContent = msg;
            $toast.classList.add('show');
            clearTimeout(showToast._t);
            showToast._t = setTimeout(function () { $toast.classList.remove('show'); }, 3000);
        }

        function copyCode() {
            runCheck();
            if (!lastCheckPassed) {
                showToast('⚠️ Erst alle Aufgaben richtig lösen, dann geht\'s zum Kopieren!');
                if (typeof $checkResult.scrollIntoView === 'function') {
                    $checkResult.scrollIntoView({ behavior: 'smooth', block: 'center' });
                }
                return;
            }
            var code = assembleFullCode(currentEx);
            copyToClipboard(code);
            showToast('✓ Code kopiert – in der Arduino IDE mit Strg+V einfügen');
        }

        function copyChatgptPrompt() {
            copyToClipboard(currentEx.prompt);
            showToast('✓ Prompt kopiert – als erste Nachricht an ChatGPT schicken');
        }

        // ---------- Zurücksetzen ----------
        function resetExercise() {
            var ok = window.confirm('Übung "' + currentEx.title + '" wirklich zurücksetzen?\nAlle eigenen Eingaben in dieser Übung gehen verloren.');
            if (!ok) return;
            state = {};
            saveStateFor(currentEx.id, state);
            renderExercise();
            showToast('↺ Übung wurde zurückgesetzt');
        }

        function resetAllButtonClicked() {
            var ok = window.confirm('Wirklich ALLE Übungen zurücksetzen?\nAlle Eingaben in allen 4 Übungen gehen verloren - gut für eine neue Klasse, aber nicht rückgängig zu machen.');
            if (!ok) return;
            resetAllExercises();
            state = loadStateFor(currentEx.id);
            renderExercise();
            showToast('🔄 Alle Übungen wurden zurückgesetzt');
        }

        // ---------- Events ----------
        $toggleCommandsButton.addEventListener('click', function () {
            var hidden = $commandsList.hidden;
            $commandsList.hidden = !hidden;
            $toggleCommandsButton.textContent = hidden ? '📖 Befehle ausblenden' : '📖 Befehle anzeigen';
        });

        document.getElementById('check-button').addEventListener('click', runCheck);
        $copyButton.addEventListener('click', copyCode);
        document.getElementById('reset-button').addEventListener('click', resetExercise);
        document.getElementById('chatgpt-copy-button').addEventListener('click', copyChatgptPrompt);
        document.getElementById('reset-all-button').addEventListener('click', resetAllButtonClicked);

        // ---------- Init ----------
        var wasExpired = clearIfExpired();

        var startIndex = 0;
        if (!wasExpired) {
            try {
                var savedIdx = parseInt(localStorage.getItem(LAST_TAB_KEY), 10);
                if (!isNaN(savedIdx) && savedIdx >= 0 && savedIdx < exercises.length) {
                    startIndex = savedIdx;
                }
            } catch (e) { /* ignore */ }
        }

        if (exercises.length) {
            selectExercise(startIndex);
            if (wasExpired) {
                showToast('🔄 Alter Stand war über 3h alt und wurde automatisch zurückgesetzt');
            }
        }
    });
})();
