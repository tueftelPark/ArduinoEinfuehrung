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
  echo Starte Arduino IDE ...
  start "" "%IDE%"
) else (
  echo [FEHLER] Arduino IDE nicht gefunden. Bitte von https://www.arduino.cc/en/software installieren.
)

REM Uebungen im Standard-Browser oeffnen
if exist "%UEBUNGEN%" (
  echo Oeffne Uebungen im Browser ...
  start "" "%UEBUNGEN%"
) else (
  echo [FEHLER] Uebungsseite nicht gefunden: %UEBUNGEN%
  pause
  goto :eof
)

if not defined IDE pause
