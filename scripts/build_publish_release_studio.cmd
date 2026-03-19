@echo off
setlocal

if "%~1"=="" (
    echo ERROR: missing executable path. Usage: build_publish_release_studio.cmd <path-to-executable>
    exit /b 1
)

REM Determine the directory of this script so we can locate the PowerShell script
set SCRIPT_DIR=%~dp0

powershell -NoProfile -ExecutionPolicy Bypass -File "%SCRIPT_DIR%publish_release_studio.ps1" -ExePath "%~1"
if errorlevel 1 exit /b 1

endlocal
exit /b 0