SET(TOOLCHAIN_PREFIX "c:/Program Files (x86)/GNU Tools ARM Embedded/6 2017-q2-update" CACHE PATH "toolchain prefix")
SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../project/stm32-cmake/cmake CACHE PATH "cmake module path")
SET(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/../project/stm32-cmake/cmake/gcc_stm32.cmake CACHE FILEPATH "toolchain file")
SET(STM32_CHIP "STM32F103RB" CACHE STRING "stm32 chip")
SET(STM32Cube_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../source/stm32_cube CACHE PATH "cube path")

#SET(STM32_LINKER_SCRIPT "./project/linker/linker.ld" CACHE FILEPATH "linker file")

