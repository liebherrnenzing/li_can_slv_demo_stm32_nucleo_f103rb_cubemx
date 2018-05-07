set RETURN_PATH=%cd%
cd source
call .\..\astyle.bat *.h *.c %* --exclude=canpie --exclude=canpie-fd_device --exclude=canpie_stm32f103_canfd --exclude=crc --exclude=li_can_slv --exclude=printf --exclude=stm32_cube --exclude=zf_log
cd %RETURN_PATH%
