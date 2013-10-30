@echo off & setlocal
::
:: Created by Martin on 17 September 2013.
::
:: Compile PhysUnits tests, GNUC
::

::set G_OPT=-DPHYS_UNITS_IN_RT_NAMESPACE

if [%1] == [-h] goto :USAGE
if [%1] == [help] goto :USAGE
if [%1] == [all] goto :ALL
if [%1] == [default] goto :DEFAULT
if [%1] == [optimize] goto :OPTIMIZE
if [%1] == [debug] goto :DEBUG
if not [%1] == [] goto :USAGE
goto :DEFAULT

:ALL
echo Default build:   && call :DEFAULT &&^
echo Optimized build: && call :OPTIMIZE &&^
echo Debug build:     && call :DEBUG
goto :EOF

:DEFAULT
call :MSGNONOPT
call :COMPILE -O0
goto :EOF

:OPTIMIZE
call :MSGOPT
call :COMPILE -O2
goto :EOF

:DEBUG
call :MSGDEBUG
::call :COMPILE -MDd -D_DEBUG
goto :EOF

:COMPILE
setlocal
set OPT=%*
g++ -Wall -Wextra -Weffc++ -std=c++11 %G_OPT% %OPT% -I../../../ -o time_performance.exe ../../Time/time_performance.cpp && time_performance
endlocal & goto :EOF

:MSGNONOPT
echo.
echo Non-optimized build...
echo.
goto :EOF

:MSGOPT
echo.
echo Optimized build: This is going to take a while...
echo.
goto :EOF

:MSGDEBUG
echo.
echo Debug build: not implemented.
echo.
goto :EOF

:USAGE
echo Usage: %0 [-h] [default] [optimize] [debug] [all] {-bo}
goto :EOF

endlocal

::
:: End of file
::
