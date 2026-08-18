#pragma once
#include <cstdint>
#include "interface.hpp"
#include "enums.hpp"
#include "types.hpp"
#include "registers.hpp"
#include "namespace.hpp"

class MPU6050
{
public:
    explicit MPU6050(II2C &i2c, uint8_t address = 0x68);

    Error begin();

    Error reset();

    Error setClockSource(ClockSource src);
    Error setAccelRange(AccelRange range);
    Error setGyroRange(GyroRange range);
    Error setDlpf(Dlpf bandwidth);
    Error setSampleRateDivider(uint8_t divider);

    AccelRange getAccelRange();
    GyroRange getGyroRange();

    Error readRawAccel(Vector3i16 &accel);
    Error readRawGyro(Vector3i16 &gyro);
    Error readTemperature(int16_t &temperature);
    Error readRawAll(IMURawData &data);

    Error readAccel(Vector3f &accel);
    Error readGyro(Vector3f &gyro);
    Error readAll(IMURawData &data);

    Error enableFIFO(bool enable);
    Error resetFIFO();
    Error getFIFOCount(uint16_t &count);
    Error readFIFO(uint8_t *data, uint16_t length);

    // To-Do Add more APIs

    Error isConnected();

    Error getDeviceId(uint8_t &id);

    Error setSleep(bool sleep);
    Error getSleep(bool &);

    Error setStandby(...);

    Error signalPathReset();

    Error setInterruptEnable();
    Error getInterruptStatus();

    Error enableTemperature();

    Error getMotionStatus();

    Error enableInterrupt(Interrupt interrupt);
    Error disableInterrupt(Interrupt interrupt);
    Error readInterruptStatus(uint8_t &status);

private:
    II2C &i2c_;
    uint8_t address_;

    Error writeRegister(uint8_t reg, uint8_t value);
    Error readRegister(uint8_t reg, uint8_t &value);

    Error readRegisters(uint8_t reg,
                        uint8_t *buffer,
                        size_t length);

    // To-Do

    Error readBit(uint8_t reg, uint8_t bit, bool &value);

    Error writeBit(uint8_t reg, uint8_t bit, bool value);

    Error readBits(uint8_t reg, uint8_t startBit, uint8_t length, uint8_t &value);

    Error writeBits(uint8_t reg, uint8_t startBit, uint8_t length, uint8_t value);
};