#include "espidf.hpp"

EspIdfI2C::EspIdfI2C(i2c_master_bus_handle_t bus)
{
    i2c_device_config_t config = {};

    config.dev_addr_length = I2C_ADDR_BIT_LEN_7;
    config.device_address = 0x68; // Default MPU6050 address
    config.scl_speed_hz = 400000;

    ESP_ERROR_CHECK(
        i2c_master_bus_add_device(bus, &config, &device_));
}

Error EspIdfI2C::write(uint8_t address,
                       uint8_t reg,
                       const uint8_t *data,
                       size_t length)
{

    if (device_ == nullptr)
    {
        return Error::DeviceNotFound;
    }
    uint8_t buffer[1 + length]; // Use std::vector for variable-sized payloads in C++.
    buffer[0] = reg;
    memcpy(buffer + 1, data, length);

    esp_err_t err =
        i2c_master_transmit(device_,
                            buffer,
                            sizeof(buffer),
                            1000);

    switch (err)
    {
    case ESP_OK:
        return Error::OK;

    case ESP_ERR_INVALID_RESPONSE: // NACK received
        return Error::Nack;

    case ESP_ERR_TIMEOUT:
        return Error::BusError;

    default:
        return Error::Undefined;
    }
}

Error EspIdfI2C::read(uint8_t address,
                      uint8_t reg,
                      uint8_t *data,
                      size_t length)
{

      if (device_ == nullptr || data == nullptr || length == 0) {
        return Error::Undefined;
    }

    esp_err_t err =
        i2c_master_transmit_receive(device_,
                           &reg,
                           1,
                           data,
                           length,
                           1000);
                           
    switch (err)
    {
    case ESP_OK:
        return Error::OK;

    case ESP_ERR_INVALID_RESPONSE: // NACK received
        return Error::Nack;

    case ESP_ERR_TIMEOUT:
        return Error::BusError;

    default:
        return Error::Undefined;
    }
}

void EspIdfDelay::delayMs(uint32_t ms)
{
    vTaskDelay(pdMS_TO_TICKS(ms));
}

void EspIdfDelay::delayUs(uint32_t us)
{
    esp_rom_delay_us(us);
}
