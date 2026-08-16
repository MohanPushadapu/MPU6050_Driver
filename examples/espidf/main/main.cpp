#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/i2c_master.h"
#include "esp_log.h"
#include "espidf.hpp"
#include "mpu6050/mpu6050.hpp"

static constexpr char TAG[] = "main";
static constexpr gpio_num_t SDA_PIN = GPIO_NUM_8;
static constexpr gpio_num_t SCL_PIN = GPIO_NUM_9;
static constexpr uint32_t I2C_FREQ_HZ = 4000000;

extern "C" void app_main(void)
{
    esp_log_level_set("*", ESP_LOG_INFO);

    i2c_master_bus_config_t bus_config_ = {};
    bus_config_.i2c_port = I2C_NUM_0;
    bus_config_.sda_io_num = SDA_PIN;
    bus_config_.scl_io_num = SCL_PIN;
    bus_config_.clk_source = I2C_CLK_SRC_DEFAULT;
    bus_config_.glitch_ignore_cnt = 7;
    bus_config_.flags.enable_internal_pullup = true;

    i2c_master_bus_handle_t bus_handle_ = nullptr;
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config_, &bus_handle_));

    EspIdfI2C bus(bus_handle_);
    EspIdfDelay time;
    MPU6050 imu(bus);

    ESP_LOGI(TAG, "IMU bus ready");

    Error err = imu.begin();

    if (err != Error::OK)
    {
        ESP_LOGE(TAG, "MPU6050 init failed");
        return; // Stops app_main; the device remains idle.
    }

    ESP_LOGI(TAG, "MPU6050 init success");

    // Equivalent to Arduino loop()
    while (true)
    {
        Vector3i16 accel;
        Vector3i16 gyro;

        Error accel_err = imu.readRawAccel(accel);
        Error gyro_err = imu.readRawGyro(gyro);

        if (accel_err == Error::OK && gyro_err == Error::OK)
        {
            ESP_LOGI(TAG,
                     "Gyro: %d, %d, %d | Accel: %d, %d, %d",
                     gyro.x, gyro.y, gyro.z,
                     accel.x, accel.y, accel.z);
        }
        else
        {
            ESP_LOGW(TAG, "MPU6050 read failed");
        }

        time.delayMs(100);
    }
}