if (TARGET tinyusb_device)
    add_executable(PID
            PID.c
            )

    # pull in common dependencies
    target_link_libraries(
        PID 
        pico_stdlib
        hardware_gpio
        )

    # enable usb output, disable uart output
    pico_enable_stdio_usb(PID 1)
    pico_enable_stdio_uart(PID 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(PID)

    set(PICO_BOARD pico_w)

elseif(PICO_ON_DEVICE)
    message(WARNING "not building stabilisation because TinyUSB submodule is not initialized in the SDK")
endif()
