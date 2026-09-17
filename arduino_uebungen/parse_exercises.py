import re, json, os

SRC_DIR = "/home/claude/arduino-editor/sources"

EXERCISES = [
    ("01_LED", "01_LED.ino"),
    ("02_Licht", "02_Licht.ino"),
    ("03_Dimmer", "03_Dimmer.ino"),
    ("04_OLED", "04_OLED.ino"),
]

TITLES = {
    "01_LED": "LED",
    "02_Licht": "Licht",
    "03_Dimmer": "Dimmer",
    "04_OLED": "OLED",
}

def read(path):
    with open(os.path.join(SRC_DIR, path), encoding="utf-8") as f:
        text = f.read()
    text = text.replace("\r\n", "\n").replace("\r", "\n")
    return text

def extract_header(text):
    lead = ""
    m = re.match(r'^(#include[^\n]*\n+)', text)
    if m:
        lead = m.group(1)
        text = text[m.end():]

    blocks = []
    raw_header_parts = []
    remaining = text
    while True:
        m = re.match(r'^\s*/\*(.*?)\*/\s*\n?', remaining, re.DOTALL)
        if not m:
            break
        blocks.append(m.group(1))
        raw_header_parts.append(remaining[:m.end()].rstrip("\n"))
        remaining = remaining[m.end():]
    raw_header = "\n\n".join(raw_header_parts)

    goal = ""
    commands = []
    for block in blocks:
        lines = block.split("\n")
        mode = None
        for line in lines:
            s = line.strip()
            if not s:
                continue
            if s.startswith(">>"):
                if "Was soll passieren" in s or "Ziel" in s:
                    mode = "goal"
                elif "Befehle" in s or "Erklärung" in s:
                    mode = "commands"
                else:
                    mode = None
                continue
            if mode == "goal":
                goal += (" " if goal else "") + s
            elif mode == "commands":
                if "<-" in s:
                    code, expl = s.split("<-", 1)
                    commands.append({"code": code.strip(), "explain": expl.strip()})
                elif commands:
                    commands[-1]["explain"] += " " + s
    return lead, goal, commands, raw_header, remaining

def find_matching_brace(text, open_idx):
    depth = 0
    for i in range(open_idx, len(text)):
        if text[i] == "{":
            depth += 1
        elif text[i] == "}":
            depth -= 1
            if depth == 0:
                return i
    return -1

def split_functions(text):
    setup_m = re.search(r'void\s+setup\s*\([^)]*\)\s*(//[^\n]*\n\s*)?\{', text)
    if not setup_m:
        return text, "", "", ""
    top = text[:setup_m.start()]
    open_idx = text.index("{", setup_m.end() - 1)
    close_idx = find_matching_brace(text, open_idx)
    setup_body = text[open_idx+1:close_idx]
    rest = text[close_idx+1:]

    loop_m = re.search(r'void\s+loop\s*\([^)]*\)\s*(//[^\n]*\n\s*)?\{', rest)
    if not loop_m:
        return top, setup_body, "", rest
    open_idx2 = rest.index("{", loop_m.end() - 1)
    close_idx2 = find_matching_brace(rest, open_idx2)
    loop_body = rest[open_idx2+1:close_idx2]
    tail = rest[close_idx2+1:]
    return top, setup_body, loop_body, tail

WORD_PLACEHOLDER_RE = re.compile(r'(?<![A-Za-z0-9_])(XX|PIN|ZEIT|FREQUENZ|WERT)(?![A-Za-z0-9_])')
QMARK_RE = re.compile(r'\?\?|\?')
CHOICE_RE = re.compile(r'\b(OUTPUT oder INPUT|HIGH oder LOW)\b')

task_counter = [0]

def split_code_comment(line):
    in_str = False
    i = 0
    n = len(line)
    while i < n - 1:
        c = line[i]
        if c == '"' and (i == 0 or line[i-1] != '\\'):
            in_str = not in_str
        elif not in_str and c == '/' and line[i+1] == '/':
            return line[:i], line[i:]
        i += 1
    return line, ""

def mask_comments(text):
    out_lines = []
    for line in text.split("\n"):
        code_part, comment_part = split_code_comment(line)
        out_lines.append(code_part + (" " * len(comment_part)))
    return "\n".join(out_lines)

def code_comment_segments(code):
    out = []
    lines = code.split("\n")
    for li, line in enumerate(lines):
        code_part, comment_part = split_code_comment(line)
        suffix = "\n" if li < len(lines) - 1 else ""
        if code_part:
            out.append({"type": "fixed", "kind": "code", "code": code_part})
        if comment_part:
            out.append({"type": "fixed", "kind": "comment", "code": comment_part})
        if suffix:
            if out and out[-1]["type"] == "fixed":
                out[-1]["code"] += suffix
            else:
                out.append({"type": "fixed", "kind": "code", "code": suffix})
    merged = []
    for seg in out:
        if merged and merged[-1]["type"] == "fixed" and merged[-1]["kind"] == seg["kind"]:
            merged[-1]["code"] += seg["code"]
        else:
            merged.append(dict(seg))
    return merged

def make_segments(chunk_text):
    segments = []
    lines = chunk_text.split("\n")
    i = 0
    fixed_buffer = []
    active_task = [None]
    pending_expects = [[]]

    def expand_inline(code):
        masked = mask_comments(code)
        matches = []
        for m in WORD_PLACEHOLDER_RE.finditer(masked):
            matches.append((m.start(), m.end(), "inline_gap", m.group(1)))
        for m in QMARK_RE.finditer(masked):
            matches.append((m.start(), m.end(), "inline_gap", m.group(0)))
        for m in CHOICE_RE.finditer(masked):
            options = ["OUTPUT", "INPUT"] if "OUTPUT" in m.group(1) else ["HIGH", "LOW"]
            matches.append((m.start(), m.end(), "inline_choice", options))
        matches.sort(key=lambda x: x[0])

        clean = []
        last_end = -1
        for start, end, kind, val in matches:
            if start < last_end:
                continue
            clean.append((start, end, kind, val))
            last_end = end
        matches = clean

        if not matches:
            return code_comment_segments(code) if code else []

        out = []
        pos = 0
        for start, end, kind, val in matches:
            if start > pos:
                out.extend(code_comment_segments(code[pos:start]))
            if active_task[0] is None:
                task_counter[0] += 1
                active_task[0] = task_counter[0]
            expect = pending_expects[0].pop(0) if pending_expects[0] else None
            if kind == "inline_gap":
                seg = {"type": "inline_gap", "task": active_task[0], "placeholder": val}
            else:
                seg = {"type": "inline_choice", "task": active_task[0], "options": val}
            if expect:
                seg["expect"] = expect
            out.append(seg)
            pos = end
        if pos < len(code):
            out.extend(code_comment_segments(code[pos:]))
        return out

    def flush_fixed(trailing_newline=False):
        if fixed_buffer:
            joined = "\n".join(fixed_buffer)
            fixed_buffer.clear()
            if joined.strip("\n") == "" and joined != "\n":
                return
            if trailing_newline and not joined.endswith("\n"):
                joined += "\n"
            segments.extend(expand_inline(joined))
            active_task[0] = None
            pending_expects[0] = []

    while i < len(lines):
        line = lines[i]
        stripped = line.strip()
        todo_m = re.match(r'^//\s*TODO:?\s*(.*)', stripped, re.IGNORECASE)
        info_m = re.match(r'^//\s*INFO:?\s*(.*)', stripped, re.IGNORECASE)

        if info_m:
            flush_fixed(trailing_newline=True)
            segments.append({"type": "info", "hint": info_m.group(1).strip()})
            i += 1
            continue

        if todo_m:
            hint = todo_m.group(1).strip()
            j = i + 1
            extra_hints = []
            expect_list = []
            while j < len(lines):
                s = lines[j].strip()
                todo_cont = re.match(r'^//\s*TODO:?\s*(.*)', s, re.IGNORECASE)
                expect_cont = re.match(r'^//\s*EXPECT:?\s*(.*)', s, re.IGNORECASE)
                if expect_cont:
                    expect_list.append(expect_cont.group(1).strip())
                    j += 1
                    continue
                if todo_cont:
                    extra_hints.append(todo_cont.group(1).strip())
                    j += 1
                    continue
                break
            full_hint = " ".join([hint] + extra_hints)

            k = j
            if j < len(lines):
                next_line = lines[j].strip()
                has_code_immediately = (next_line != "" and not next_line.startswith("//"))
            else:
                has_code_immediately = False

            flush_fixed(trailing_newline=True)
            task_counter[0] += 1
            if not has_code_immediately:
                seg = {"type": "gap", "task": task_counter[0], "hint": full_hint}
                if expect_list:
                    seg["expect"] = expect_list[0]
                segments.append(seg)
                active_task[0] = None
                pending_expects[0] = []
                i = k
            else:
                segments.append({"type": "label", "task": task_counter[0], "hint": full_hint})
                active_task[0] = task_counter[0]
                pending_expects[0] = list(expect_list)
                i = j
            continue
        else:
            fixed_buffer.append(line)
            i += 1
    flush_fixed()
    return segments

def parse_exercise(id_, relpath):
    task_counter[0] = 0
    raw = read(relpath)
    lead, goal, commands, raw_header, rest = extract_header(raw)
    top, setup_body, loop_body, tail = split_functions(rest)

    result = {
        "id": id_,
        "title": TITLES.get(id_, id_.split("_", 1)[1].replace("_", " ")),
        "goal": goal,
        "commands": commands,
        "lead": lead.strip("\n"),
        "raw_header": raw_header,
        "top": make_segments(top.strip("\n")),
        "setup": make_segments(setup_body.strip("\n")),
        "loop": make_segments(loop_body.strip("\n")),
        "task_count": None
    }
    result["task_count"] = task_counter[0]
    return result

all_exercises = []
for id_, relpath in EXERCISES:
    ex = parse_exercise(id_, relpath)
    all_exercises.append(ex)
    print(f"OK  {id_}: {ex['task_count']} Aufgaben")

# Zusatz 5: ChatGPT-Prompt (kein Code-Übungstyp, eigener "chatgpt"-Typ)
chatgpt_text = open(os.path.join(SRC_DIR, "zusatz5_chatgpt_prompt.txt"), encoding="utf-8").read()
m = re.search(r'-------- AB HIER KOPIEREN.*?--------\n\n(.*?)\n\n-------- BIS HIER KOPIEREN --------', chatgpt_text, re.DOTALL)
chatgpt_prompt = m.group(1).strip()

all_exercises.append({
    "id": "05_ChatGPT",
    "title": "ChatGPT",
    "kind": "chatgpt",
    "goal": "Jetzt baut ihr euer eigenes Projekt! Kopiert den Startprompt unten und schickt ihn als erste Nachricht an ChatGPT. Danach könnt ihr ChatGPT in eigenen Worten sagen, was euer Programm machen soll - nennt dabei einfach die Bauteile beim Namen (LED, Button, Buzzer, Lichtsensor, Poti, OLED-Bildschirm). ChatGPT gibt euch dann immer den kompletten Code zum Einfügen in die Arduino IDE.",
    "prompt": chatgpt_prompt,
    "components_source": "https://sensorkit.arduino.cc/",
    "components": [
        {"name": "LED", "desc": "Eine einfache Leuchtdiode. Kann ein-/ausgeschaltet oder gedimmt (heller/dunkler gemacht) werden.", "idea": "Idee: Alarmlampe, Ampel, Disco-Blinklicht"},
        {"name": "Button", "desc": "Ein Taster/Knopf. Erkennt, ob er gerade gedrückt wird (HIGH) oder nicht (LOW).", "idea": "Idee: Klingel, Quiz-Buzzer, Geheimcode-Schalter"},
        {"name": "Potentiometer (Poti)", "desc": "Ein Drehknopf. Beim Drehen verändert sich ein Messwert - damit lassen sich z.B. Helligkeit oder Lautstärke einstellen.", "idea": "Idee: Lautstärkeregler, Dimmer, Tempo-Regler für ein Spiel"},
        {"name": "Buzzer", "desc": "Ein kleiner Lautsprecher. Kann Töne in verschiedenen Tonhöhen abspielen.", "idea": "Idee: Wecker, Alarm, kleine Melodie nachspielen"},
        {"name": "Lichtsensor", "desc": "Misst, wie hell oder dunkel es gerade ist.", "idea": "Idee: automatische Nachtlampe, Sonnenaufgangs-Wecker"},
        {"name": "Sound-Sensor", "desc": "Ein kleines Mikrofon. Misst, wie laut es gerade ist bzw. erkennt Geräusche/Schwingungen.", "idea": "Idee: klatsch-gesteuerte Lampe, Lautstärke-Warner"},
        {"name": "OLED-Bildschirm", "desc": "Ein kleiner Bildschirm. Zeigt Text, Zahlen oder einfache Zeichnungen an.", "idea": "Idee: eigene Uhr, Mini-Spiel, Namens-/Textanzeige"},
        {"name": "Luftdrucksensor", "desc": "Misst den Luftdruck der Umgebung (über I2C).", "idea": "Idee: einfache Wettervorhersage, Höhenmesser"},
        {"name": "Temperatursensor", "desc": "Misst Temperatur und Luftfeuchtigkeit.", "idea": "Idee: Zimmer-Thermometer, Warnung bei zu grosser Hitze"},
        {"name": "Beschleunigungssensor", "desc": "Erkennt Bewegung und Ausrichtung (z.B. ob das Board gekippt oder geschüttelt wird).", "idea": "Idee: Schrittzähler, Wackel-Alarm, Neige-Spiel"},
    ],
    "combos": [
        "Lichtsensor + LED = eine Lampe, die sich von selbst einschaltet, wenn es dunkel wird",
        "Button + Buzzer + LED = ein kleines Quiz-Spiel mit Signalton und Lämpchen",
        "Poti + OLED = eine Anzeige, die sich live verändert, wenn du am Drehknopf drehst",
        "Sound-Sensor + LED = eine Lampe, die angeht, wenn du in die Hände klatschst",
        "Beschleunigungssensor + Buzzer = ein Alarm, der losgeht, wenn das Board bewegt wird",
    ],
    "task_count": 0,
})
print("OK  05_ChatGPT: Zusatzaufgabe (Prompt)")

with open("/home/claude/arduino-editor/exercises.json", "w", encoding="utf-8") as f:
    json.dump(all_exercises, f, ensure_ascii=False, indent=2)

print("\nGespeichert:", len(all_exercises), "Übungen")
