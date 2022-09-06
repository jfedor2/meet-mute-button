cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_PATH "${CMAKE_CURRENT_LIST_DIR}/pico-sdk")
set(PICO_TINYUSB_PATH "${CMAKE_CURRENT_LIST_DIR}/tinyusb")

include(pico_sdk_import.cmake)

project(mute_button)

pico_sdk_init()

add_compile_options(-Wall)

add_executable(mute_button src/mute_button.cc src/tinyusb_stuff.cc src/our_descriptor.cc src/ws2812.cc)

pico_generate_pio_header(mute_button ${CMAKE_CURRENT_LIST_DIR}/src/ws2812.pio)

target_include_directories(mute_button PRIVATE src)

target_link_libraries(mute_button pico_stdlib hardware_pio tinyusb_device tinyusb_board)

pico_add_extra_outputs(mute_button)
