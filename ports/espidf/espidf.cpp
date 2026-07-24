#include "espidf.hpp"

namespace mpu6050
{

EspIdfI2C::EspIdfI2C(i2c_master_bus_handle_t bus)
{
    i2c_device_config_t config = {};

    config.dev_addr_length = I2C_ADDR_BIT_LEN_7;
    config.device_address  = 0x68;        // Default MPU6050 address
    config.scl_speed_hz    = 400000;

    ESP_ERROR_CHECK(
        i2c_master_bus_add_device(bus, &config, &device_));
}

Error EspIdfI2C::write(uint8_t address,
                       const uint8_t* data,
                       size_t length)
{
    esp_err_t err =
        i2c_master_transmit(device_,
                            data,
                            length,
                            -1);

    return (err == ESP_OK) ?
            Error::OK :
            Error::I2C_WRITE_FAILED;
}

Error EspIdfI2C::read(uint8_t address,
                      uint8_t* data,
                      size_t length)
{
    esp_err_t err =
        i2c_master_receive(device_,
                           data,
                           length,
                           -1);

    return (err == ESP_OK) ?
            Error::OK :
            Error::I2C_READ_FAILED;
}

void EspIdfDelay::delayMs(uint32_t ms)
{
    vTaskDelay(pdMS_TO_TICKS(ms));
}

void EspIdfDelay::delayUs(uint32_t us)
{
    esp_rom_delay_us(us);
}

} // namespace mpu6050