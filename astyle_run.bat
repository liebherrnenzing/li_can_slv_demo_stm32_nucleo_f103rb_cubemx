set RETURN_PATH=%cd%
cd source
call .\..\astyle.bat *.h *.c %* --exclude=canpie --exclude=canpie-fd_device --exclude=freertos --exclude=li_can_slv --exclude=printf --exclude=stm32_cube --exclude=zf_log
cd %RETURN_PATH%
