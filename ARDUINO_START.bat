@echo off
chcp 65001 >nul
setlocal
title tueftelPark - Arduino starten

set "DIR=%~dp0"
set "UEBUNGEN=%DIR%arduino_uebungen 2\00_arduino_uebungen.html"

REM Arduino IDE suchen (IDE 2.x und 1.x, Benutzer- und Systeminstallation)
set "IDE="
if exist "%LOCALAPPDATA%\Programs\Arduino IDE\Arduino IDE.exe" set "IDE=%LOCALAPPDATA%\Programs\Arduino IDE\Arduino IDE.exe"
if not defined IDE if exist "%ProgramFiles%\Arduino IDE\Arduino IDE.exe" set "IDE=%ProgramFiles%\Arduino IDE\Arduino IDE.exe"
if not defined IDE if exist "%ProgramFiles%\Arduino\arduino.exe" set "IDE=%ProgramFiles%\Arduino\arduino.exe"
if not defined IDE if exist "%ProgramFiles(x86)%\Arduino\arduino.exe" set "IDE=%ProgramFiles(x86)%\Arduino\arduino.exe"

if defined IDE (
  call :neuer_sketch
  echo Starte Arduino IDE mit neuem Sketch ...
  REM Ueber WMI starten: die IDE laeuft so unabhaengig vom Konsolenfenster
  powershell -NoProfile -Command "$q=[char]34; $r=Invoke-CimMethod -ClassName Win32_Process -MethodName Create -Arguments @{CommandLine=$q+$env:IDE+$q+' '+$q+$env:SKETCH+$q}; if ($r.ReturnValue -ne 0) { exit 1 }" >nul 2>&1 || start "" "%IDE%" "%SKETCH%"
) else (
  echo [FEHLER] Arduino IDE nicht gefunden. Bitte von https://www.arduino.cc/en/software installieren.
)

REM Uebungen im Standard-Browser oeffnen
if exist "%UEBUNGEN%" (
  echo Oeffne Uebungen im Browser ...
  explorer.exe "%UEBUNGEN%"
) else (
  echo [FEHLER] Uebungsseite nicht gefunden: %UEBUNGEN%
  pause
  goto :eof
)

if not defined IDE pause
exit

REM ------------------------------------------------------------
REM Neuen leeren Sketch im Sketchbook anlegen (Name mit Zeitstempel)
REM ------------------------------------------------------------
:neuer_sketch
set "SKETCHBOOK=%USERPROFILE%\Documents\Arduino"
for /f %%t in ('powershell -NoProfile -Command "Get-Date -Format yyyyMMdd_HHmmss"') do set "STAMP=%%t"
set "NAME=sketch_%STAMP%"
set "SKETCHDIR=%SKETCHBOOK%\%NAME%"
set "SKETCH=%SKETCHDIR%\%NAME%.ino"
if not exist "%SKETCHDIR%" mkdir "%SKETCHDIR%"
(
  echo void setup^(^) {
  echo   // put your setup code here, to run once:
  echo.
  echo }
  echo.
  echo void loop^(^) {
  echo   // put your main code here, to run repeatedly:
  echo.
  echo }
) > "%SKETCH%"
call :board_waehlen
goto :eof

REM ------------------------------------------------------------
REM Angeschlossenes Board suchen und im Sketch hinterlegen
REM (sketch.yaml: default_fqbn / default_port, ab Arduino IDE 2.3)
REM ------------------------------------------------------------
:board_waehlen
set "CLI="
if exist "%DIR%arduino-cli.exe" set "CLI=%DIR%arduino-cli.exe"
if not defined CLI goto :eof

echo Suche angeschlossenes Board ...
set "PORT="
set "FQBN="
set "BOARDLIST=%TEMP%\tp_boardlist.txt"
"%CLI%" board list > "%BOARDLIST%" 2>nul

REM 1. Board, das arduino-cli erkennt (Port und FQBN aus der Liste)
for /f "tokens=1" %%p in ('findstr /r "^COM[0-9]" "%BOARDLIST%" ^| findstr /r " arduino:[a-z0-9_]*:[a-z0-9_]*"') do if not defined PORT set "PORT=%%p"
if defined PORT for /f "tokens=*" %%l in ('findstr /b "%PORT% " "%BOARDLIST%"') do call :fqbn_suchen %%l

REM 2. Sonst erster USB-Port (z.B. Nachbau mit CH340) als Arduino Uno
if not defined PORT for /f "tokens=1" %%p in ('findstr /r "^COM[0-9]" "%BOARDLIST%" ^| findstr /i "(USB)"') do if not defined PORT set "PORT=%%p"
if defined PORT if not defined FQBN set "FQBN=arduino:avr:uno"

del "%BOARDLIST%" >nul 2>&1
if not defined PORT (
  echo Kein Board angeschlossen - Board kann in der IDE gewaehlt werden.
  goto :eof
)
echo Board %FQBN% an %PORT% gefunden.
"%CLI%" board attach -p %PORT% -b %FQBN% "%SKETCHDIR%" >nul 2>&1
goto :eof

:fqbn_suchen
if "%~1"=="" goto :eof
echo %~1| findstr /r "^arduino:[a-z0-9_]*:[a-z0-9_]*$" >nul && if not defined FQBN set "FQBN=%~1"
shift
goto fqbn_suchen
