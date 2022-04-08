if (TARGET tinyusb_device)
    add_executable(hello_espruino
            hello_espruino.c
            )

    # pull in common dependencies
    target_link_libraries(hello_espruino pico_stdlib)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(hello_espruino 1)
    pico_enable_stdio_uart(hello_espruino 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(hello_espruino)

    # add url via pico_set_program_url
    example_auto_set_url(hello_espruino)
elseif(PICO_ON_DEVICE)
    message(WARNING "not building hello_usb because TinyUSB submodule is not initialized in the SDK")
endif()
