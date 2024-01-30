if (TARGET tinyusb_device)
    add_executable(control
            control.c
            )

    # pull in common dependencies
    target_link_libraries(
        control 
        pico_stdlib
        hardware_gpio
        )

    # enable usb output, disable uart output
    pico_enable_stdio_usb(control 1)
    pico_enable_stdio_uart(control 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(control)

    set(PICO_BOARD pico_w)

elseif(PICO_ON_DEVICE)
    message(WARNING "not building stabilisation because TinyUSB submodule is not initialized in the SDK")
endif()
