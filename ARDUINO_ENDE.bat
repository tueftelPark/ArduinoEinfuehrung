@echo off
chcp 65001 >nul
setlocal
title tueftelPark - Sensorkit zuruecksetzen

set "FQBN=arduino:avr:uno"
set "FEEDBACK=https://www.tuefteln.com/feedback"
set "DIR=%~dp0"

REM arduino-cli neben dem Skript bevorzugen, sonst aus dem PATH
set "CLI=arduino-cli"
if exist "%DIR%arduino-cli.exe" set "CLI=%DIR%arduino-cli.exe"

call "%CLI%" version >nul 2>&1 || (
  echo [FEHLER] arduino-cli nicht gefunden. Lege arduino-cli.exe in diesen Ordner.
  goto ende
)

REM Core und Bibliothek nur installieren, wenn sie fehlen
call "%CLI%" core list | findstr /i "arduino:avr" >nul || (
  echo Installiere Arduino AVR Core ...
  call "%CLI%" core update-index && call "%CLI%" core install arduino:avr
)
call "%CLI%" lib list | findstr /i "Arduino_SensorKit" >nul || (
  echo Installiere Bibliothek Arduino_SensorKit ...
  call "%CLI%" lib install "Arduino_SensorKit"
)

REM Port suchen: zuerst echter Uno, sonst erster COM-Port
set "PORT="
for /f "tokens=1" %%p in ('call "%CLI%" board list ^| findstr /i "%FQBN%"') do if not defined PORT set "PORT=%%p"
if not defined PORT for /f "tokens=1" %%p in ('call "%CLI%" board list ^| findstr /r "^COM[0-9]"') do if not defined PORT set "PORT=%%p"
if not defined PORT (
  echo [FEHLER] Kein Arduino gefunden. Erkannte Ports:
  call "%CLI%" board list
  goto ende
)
echo Arduino gefunden an %PORT%

echo.
echo Display wird geleert und Sensorkit zurueckgesetzt ...
call "%CLI%" compile --upload -p %PORT% -b %FQBN% "%DIR%sketches\display_leeren" || goto fehler

echo.
echo Fertig! Das Sensorkit ist zurueckgesetzt.
start "" "%FEEDBACK%"
goto ende

:fehler
echo [FEHLER] Hochladen fehlgeschlagen. Ist die Arduino IDE noch offen? Bitte schliessen und nochmals starten.

:ende
echo.
pause
