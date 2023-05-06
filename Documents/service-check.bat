@echo off
set LOG_FILE=service_check.log
set SERVICES=Grafana InfluxDB my-telegraf telegraf

echo Checking if the following services are installed and running: %SERVICES%

for %%i in (%SERVICES%) do (
    echo Checking if %%i is installed...
    sc query "%%i" >nul 2>nul
    if %errorlevel% equ 0 (
        echo The service %%i is installed..
        sc query "%%i" | find "RUNNING" >nul 2>nul
        if %errorlevel% equ 0 (
            echo The service %%i is running.
            echo %date% %time% - %%i is installed and running. >> %LOG_FILE%
        ) else (
            echo The service %%i is installed but not running.
            echo %date% %time% - %%i is installed but not running. >> %LOG_FILE%
        )
    ) else (
        echo The service %%i is not installed.
        echo %date% %time% - %%i is not installed. >> %LOG_FILE%
    )
)

echo Check complete. The log file is located at %cd%\%LOG_FILE%

PAUSE