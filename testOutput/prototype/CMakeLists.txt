if (TARGET tinyusb_device)

    include_directories(include)
    add_executable(main
            main.c
            IMU.c
            motor.c
            )

    # pull in common dependencies
    target_link_libraries(
        main 
        pico_stdlib
        hardware_i2c
        hardware_pwm
        )

    # enable usb output, disable uart output
    pico_enable_stdio_usb(main 1)
    pico_enable_stdio_uart(main 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(main)

elseif(PICO_ON_DEVICE)
    message(WARNING "not building stabilisation because TinyUSB submodule is not initialized in the SDK")
endif()
