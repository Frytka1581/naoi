@echo off
set /a i=0

:main

set /a i=i+1

echo %i% > ziarno.txt

type ziarno.txt | gener.exe > wejscie.in

type wejscie.in | brut.exe > brutOut.out
type wejscie.in | wzor.exe > wzorOut.out

fc wzorOut.out brutOut.out > nul

if errorlevel 1 goto error

:next

echo OK %i%
goto main

:error

echo NIEEEE %i%

pause
