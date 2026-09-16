@echo off
setlocal
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0..\..\BUILD-TEST.ps1" -Suite rt_view_domain %*
exit /b %errorlevel%
