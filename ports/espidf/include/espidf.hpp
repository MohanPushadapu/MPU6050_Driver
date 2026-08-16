#pragma once

#include "mpu6050/mpu6050.hpp"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_rom_sys.h>
#include <driver/i2c_master.h>
#include <cstring>

#include "mpu6050/interface.hpp"

class EspIdfI2C : public II2C
{
public:
    explicit EspIdfI2C(i2c_master_bus_handle_t bus);

    Error write(uint8_t address,
                uint8_t reg,
                const uint8_t *data,
                size_t length) override;

    Error read(uint8_t address,
               uint8_t reg,
               uint8_t *data,
               size_t length) override;

private:
    i2c_master_bus_handle_t bus_;
    i2c_master_dev_handle_t device_;
};

class EspIdfDelay : public IDelay
{
public:
    void delayMs(uint32_t ms) override;
    void delayUs(uint32_t us) override;
};
