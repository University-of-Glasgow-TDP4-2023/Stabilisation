if (TARGET tinyusb_device)
    add_executable(stabilisation
            stabilisation.c
            )

    # pull in common dependencies
    target_link_libraries(
        stabilisation 
        pico_stdlib
        hardware_i2c
        )

    # enable usb output, disable uart output
    pico_enable_stdio_usb(stabilisation 1)
    pico_enable_stdio_uart(stabilisation 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(stabilisation)

elseif(PICO_ON_DEVICE)
    message(WARNING "not building stabilisation because TinyUSB submodule is not initialized in the SDK")
endif()
