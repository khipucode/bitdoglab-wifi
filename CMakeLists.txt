cmake_minimum_required(VERSION 3.13)

set(PICO_BOARD pico_w)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(bitdoglab_wifi C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_subdirectory(lib/ssd1306)

add_executable(bitdoglab_wifi main.c)

pico_enable_stdio_usb(bitdoglab_wifi 1)
pico_enable_stdio_uart(bitdoglab_wifi 0)
pico_add_extra_outputs(bitdoglab_wifi)

target_link_libraries(bitdoglab_wifi
    pico_stdlib
    pico_cyw43_arch_lwip_poll
    hardware_i2c
    ssd1306
)

target_include_directories(bitdoglab_wifi PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/ssd1306
)
