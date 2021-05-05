set(example "AllLogLevels")

add_executable(${example} ${example}.ino)

target_link_libraries(${example} PUBLIC
    RF24Log
    pico_stdlib
    )

pico_enable_stdio_usb(${example} 1)
pico_enable_stdio_uart(${example} 0)
pico_add_extra_outputs(${example})
