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
call :COMPILE
goto :EOF

:OPTIMIZE
call :AWHILE
call :COMPILE -O2
goto :EOF

:DEBUG
call :COMPILE -MDd -D_DEBUG
goto :EOF

:COMPILE
setlocal
set OPT=%*
:: ../../Test/TestInput.cpp
g++ -Wall -Wextra -Weffc++ -std=c++11 %G_OPT% %OPT% -I../../../ -o test_quantity.exe ../../Test/test_quantity.cpp && test_quantity
g++ -Wall -Wextra -Weffc++ -std=c++11 %G_OPT% %OPT% -I../../../ -o test_quantity_io.exe ../../Test/test_quantity_io.cpp && test_quantity_io
::clang++ -Wall %G_OPT% %OPT% -I../../../ -o test_quantity.exe ../../Test/test_quantity.cpp && test_quantity
endlocal & goto :EOF

:AWHILE
echo.
echo This is going to take a while...
echo.
goto :EOF

:USAGE
echo Usage: %0 [-h] [default] [optimize] [debug] [all] {-bo}
goto :EOF

endlocal

::
:: End of file
::
