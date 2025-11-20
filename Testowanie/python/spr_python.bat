@echo off
set /a i=0

:main

set /a i=i+1

echo %i% > ziarno.txt

python3 gener.py > wejscie.in

python3 brut.py < wejscie.in > brutOut.out
python3 wzor.py < wejscie.in > wzorOut.out

fc wzorOut.out brutOut.out > nul

if errorlevel 1 goto error

:next

echo OK %i%
goto main

:error

echo NIEEEE %i%

pause
