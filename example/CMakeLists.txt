cmake_minimum_required(VERSION 3.7)
project(MAX7219)

enable_language(ASM)

set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-as)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -DSTM32F103xB")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -DSTM32F103xB")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Xlinker --gc-sections --specs=nosys.specs -TSTM32F103RBTx_FLASH.ld")

include_directories(Inc Drivers/CMSIS/Include Drivers/CMSIS/Device/ST/STM32F1xx/Include Drivers/STM32F1xx_HAL_Driver/Inc Drivers/MAX7219)

aux_source_directory(Src SOURCES)
aux_source_directory(Drivers/STM32F1xx_HAL_Driver/Src HAL_SOURCES)
set(STARTUP_SOURCES startup/startup_stm32f103xb.s)
aux_source_directory(Drivers/MAX7219 MAX7219_SOURCES)

configure_file(STM32F103RBTx_FLASH.ld STM32F103RBTx_FLASH.ld)

add_executable(MAX7219 ${MAX7219_SOURCES} ${SOURCES} ${HAL_SOURCES} ${STARTUP_SOURCES})