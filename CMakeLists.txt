idf_component_register(
    SRCS
        "src/mpu6050.cpp"
        "ports/espidf/src/espidf.cpp"
    
    INCLUDE_DIRS
        "include"
        "ports/espidf/include"

    PRIV_REQUIRES
        esp_driver_i2c
        freertos
        log
        driver
)