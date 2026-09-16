@echo off
setlocal
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0..\..\BUILD-TEST.ps1" -Suite twilight_two_player_lights %*
exit /b %errorlevel%
