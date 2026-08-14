#pragma once

#include <Arduino.h>
#include <Wire.h>

#include "mpu6050/interface.hpp"
#include "mpu6050/errors.hpp"

class ArduinoI2C : public II2C
{
public:
    explicit ArduinoI2C(TwoWire &wire = Wire);

    Error begin();

    Error write(
        uint8_t address,
        uint8_t reg,
        const uint8_t *data,
        size_t length) override;

    Error read(
        uint8_t address,
        uint8_t reg,
        uint8_t *data,
        size_t length) override;

    private:
        TwoWire& wire_;
};