@echo off
setlocal
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0..\..\BUILD-TEST.ps1" -Suite animal_replay_identity %*
exit /b %errorlevel%
