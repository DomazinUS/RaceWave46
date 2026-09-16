@echo off
setlocal
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0..\..\BUILD-TEST.ps1" -Suite dolphin_free_ride_settings %*
exit /b %errorlevel%
