idf_component_register(SRCS "main.cpp"
                    INCLUDE_DIRS "."
                    REQUIRES MPU6050_Driver esp_driver_i2c freertos)