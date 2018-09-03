PROJECT(li_can_slv_demo_stm32_nucleo_f103rb_cubemx)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
ENABLE_LANGUAGE(ASM)

FIND_PACKAGE(CMSIS REQUIRED)
FIND_PACKAGE(STM32LL COMPONENTS usart REQUIRED)
FIND_PACKAGE(STM32HAL COMPONENTS gpio can tim uart usart REQUIRED)

INCLUDE_DIRECTORIES(
    ${CMSIS_INCLUDE_DIRS}
    ${STM32HAL_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/source
    ${CMAKE_CURRENT_SOURCE_DIR}/source/crc
    ${CMAKE_CURRENT_SOURCE_DIR}/source/printf       
    ${CMAKE_CURRENT_SOURCE_DIR}/source/zf_log/zf_log
    
    # canpie
    ${CMAKE_CURRENT_SOURCE_DIR}/source/canpie/source/canpie-fd
    
    # canpie device
    # use this for our driver    
    ${CMAKE_CURRENT_SOURCE_DIR}/source/canpie-fd_device/stm32/f1/hal
# use the next line for the microcontrol driver    
#    ${CMAKE_CURRENT_SOURCE_DIR}/source/canpie_stm32f103_canfd

	# li_can_slv
    ${CMAKE_CURRENT_SOURCE_DIR}/source/li_can_slv/include
    ${CMAKE_CURRENT_SOURCE_DIR}/source/li_can_slv/include/li_can_slv/arch
    ${CMAKE_CURRENT_SOURCE_DIR}/source/li_can_slv/include/li_can_slv/arch/canpie_adapter
    
    # li_can_slv and app user specific implementation
    ${CMAKE_CURRENT_SOURCE_DIR}/source/li_can_slv_hw
    ${CMAKE_CURRENT_SOURCE_DIR}/source/li_can_slv/include
    ${CMAKE_CURRENT_SOURCE_DIR}/source/li_can_slv_xload_handler
    
    ${CMAKE_CURRENT_SOURCE_DIR}/source/io_app
    ${CMAKE_CURRENT_SOURCE_DIR}/source/io_app_hw    
    ${CMAKE_CURRENT_SOURCE_DIR}/source/io_app_conv

    ${CMAKE_CURRENT_SOURCE_DIR}/source/io_app_ma_w
)

SET(PROJECT_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/source/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/newlib.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/stm32f1xx_it.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/stm32f1xx_hal_msp.c
        
    ${CMAKE_CURRENT_SOURCE_DIR}/source/printf/printf.c

    ${CMAKE_CURRENT_SOURCE_DIR}/source/canpie/source/canpie-fd/cp_msg.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/canpie/source/canpie-fd/cp_fifo.c
# use this for our driver
    ${CMAKE_CURRENT_SOURCE_DIR}/source/canpie-fd_device/stm32/hal/stm32_canpie-fd.c
# use the next line for the microcontrol driver
#	${CMAKE_CURRENT_SOURCE_DIR}/source/canpie_stm32f103_canfd/stm32f103_canfd.c
     
     
    ${CMAKE_CURRENT_SOURCE_DIR}/source/li_can_slv/source/api/li_can_slv_api.c

    ${CMAKE_CURRENT_SOURCE_DIR}/source/li_can_slv/source/arch/canpie_adapter/io_can_async_hw.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/li_can_slv/source/arch/canpie_adapter/io_can_hw.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/li_can_slv/source/arch/canpie_adapter/io_can_main_hw_handler.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/li_can_slv/source/arch/canpie_adapter/io_can_main_hw.c
    #${CMAKE_CURRENT_SOURCE_DIR}/source/li_can_slv/source/arch/canpie_adapter/io_can_mon_hw.c

    ${CMAKE_CURRENT_SOURCE_DIR}/source/li_can_slv/source/async/io_can_async_handler.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/li_can_slv/source/async/io_can_async.c

    ${CMAKE_CURRENT_SOURCE_DIR}/source/li_can_slv/source/config/io_can_config.c

    ${CMAKE_CURRENT_SOURCE_DIR}/source/li_can_slv/source/core/io_can_main_handler.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/li_can_slv/source/core/io_can_main.c
    #${CMAKE_CURRENT_SOURCE_DIR}/source/li_can_slv/source/core/io_can_mon.c

    #${CMAKE_CURRENT_SOURCE_DIR}/source/li_can_slv/source/core/io_can_reconnect.c

    ${CMAKE_CURRENT_SOURCE_DIR}/source/li_can_slv/source/core/io_can.c

    ${CMAKE_CURRENT_SOURCE_DIR}/source/li_can_slv/source/error/io_can_errno.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/li_can_slv/source/error/io_can_error.c

    ${CMAKE_CURRENT_SOURCE_DIR}/source/li_can_slv/source/sync/io_can_sync_handler.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/li_can_slv/source/sync/io_can_sync.c

    ${CMAKE_CURRENT_SOURCE_DIR}/source/li_can_slv/source/sys/io_can_sys.c

    #${CMAKE_CURRENT_SOURCE_DIR}/source/li_can_slv/source/xload/li_can_slv_xload_buffer.c
    #${CMAKE_CURRENT_SOURCE_DIR}/source/li_can_slv/source/xload/li_can_slv_xload_info.c
    #${CMAKE_CURRENT_SOURCE_DIR}/source/li_can_slv/source/xload/li_can_slv_xload.c

    #${CMAKE_CURRENT_SOURCE_DIR}/source/crc/crc_xmodem.c
    #${CMAKE_CURRENT_SOURCE_DIR}/source/li_can_slv_hw/li_can_slv_xload_info_crc.c
    
    #${CMAKE_CURRENT_SOURCE_DIR}/source/li_can_slv_xload_handler/li_can_slv_xload_handler.c
    
    ${CMAKE_CURRENT_SOURCE_DIR}/source/io_app/io_app_module_change.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/io_app_conv/io_app_convc.c
    
    ${CMAKE_CURRENT_SOURCE_DIR}/source/io_app_ma_w/io_app_ma_w.c
    
    ${CMAKE_CURRENT_SOURCE_DIR}/source/io_app_hw/io_app_demo_hw.c
    
    ${CMAKE_CURRENT_SOURCE_DIR}/source/zf_log/zf_log/zf_log.c
)

add_definitions(-DSTM32F103xB)
add_definitions(-DZF_LOG)
add_definitions(-DZF_LOG_CONFIG)
add_definitions(-DPRINTF_CONFIG)
#add_definitions(-DCP_DEBUG=1)
add_definitions(-DCP_DEVICE_TX_STRATEGY_ROLL)

# add this for the microcontrol driver
#add_definitions(-DDISABLE_HAL_CAN_IRQ)


SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -gdwarf-4 -g3 -O0")

SET(CMAKE_C_FLAGS_DEBUG "-O0 -g" CACHE INTERNAL "c compiler flags debug")

SET(STM32_MIN_HEAP_SIZE "0x400")
		
ADD_EXECUTABLE(${CMAKE_PROJECT_NAME} ${PROJECT_SOURCES} ${CMSIS_SOURCES}  ${STM32LL_SOURCES} ${STM32HAL_SOURCES})

TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME})

STM32_SET_TARGET_PROPERTIES(${CMAKE_PROJECT_NAME})
STM32_ADD_HEX_BIN_TARGETS(${CMAKE_PROJECT_NAME})
STM32_PRINT_SIZE_OF_TARGETS(${CMAKE_PROJECT_NAME})
STM32_ADD_DUMP_TARGET(${CMAKE_PROJECT_NAME})

message("Generated with config types: ${CMAKE_CONFIGURATION_TYPES}")
