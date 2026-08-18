idf_component_register(
    SRCS
        "src/mpu6050.cpp"
    INCLUDE_DIRS
        "include"
    PRIV_REQUIRES freertos esp_driver_i2c
)

add_subdirectory(ports/espidf)