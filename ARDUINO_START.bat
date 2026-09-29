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
goto :eof
