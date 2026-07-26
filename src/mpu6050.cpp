#include "mpu6050/mpu6050.hpp"
#include "mpu6050/interface.hpp"

MPU6050::MPU6050(II2C &i2c, uint8_t address) : i2c_(i2c), address_(address)
{
}

Error MPU6050::writeRegister(uint8_t reg, uint8_t value)
{
    return i2c_.write(address_, reg, &value, 1);
}

Error MPU6050::readRegister(uint8_t reg, uint8_t &value)
{
    return i2c_.read(address_, reg, &value, 1);
}

Error MPU6050::readRegisters(uint8_t reg, uint8_t *buffer, size_t length)
{
    return i2c_.read(address_, reg, buffer, length);
}

//  read and write bits
Error MPU6050::readBit(uint8_t reg, uint8_t bit, bool &value)
{
    uint8_t regValue;

    Error err = readRegister(reg, regValue);

    if (err != Error::OK)
    {
        return err;
    }
    value = (regValue & (1 << bit)) != 0;

    return Error::OK;
}

Error MPU6050::readBits(uint8_t reg, uint8_t startBit, uint8_t length, uint8_t &value)
{

    // To-Do:: Add validation parameters.

    uint8_t regValue;

    Error err = readRegister(reg, regValue);

    if (err != Error::OK)
    {
        return err;
    }

    uint8_t mask = ((1U << length) - 1U) << startBit;

    value = (regValue & mask) >> startBit;

    return Error::OK;
}

Error MPU6050::writeBit(uint8_t reg, uint8_t bit, bool value)
{
    uint8_t regValue;

    Error err = readRegister(reg, regValue);

    if (err != Error::OK)
    {
        return err;
    }
    if (value)
        regValue |= (1 << bit);
    else
        regValue &= ~(1 << bit);

    return writeRegister(reg, regValue);
}

Error MPU6050::writeBits(uint8_t reg, uint8_t startBit, uint8_t length, uint8_t value)
{
    uint8_t regValue;

    Error err = readRegister(reg, regValue);

    if (err != Error::OK)
    {
        return err;
    }

    uint8_t mask = ((1U << length) - 1U) << startBit;

    regValue &= ~mask;

    regValue |= (value << startBit) & mask;

    return writeRegister(reg, regValue);
}

Error MPU6050::begin()
{
    Error err;

    err = reset();

    if (err != Error::OK)
    {
        return err;
    }
    
    uint8_t whoAmI;
    err = readRegister(reg::WHO_AM_I, whoAmI);
    if (err != Error::OK)
        return err;

    // if (whoAmI != 0x68 && whoAmI != 0x69)
    //     return Error::DeviceNotFound;

    // Wake the device
    // err = setSleep(false);
    // if (err != Error::OK)
    //     return err;

    // Select PLL with X gyro reference
    err = setClockSource(ClockSource::XPLL);
    if (err != Error::OK)
        return err;

    // Configure default ranges
    err = setGyroRange(GyroRange::DPS250);
    if (err != Error::OK)
        return err;

    err = setAccelRange(AccelRange::G2);
    if (err != Error::OK)
        return err;

    // Configure default filter
    err = setDlpf(Dlpf::BW42);
    if (err != Error::OK)
        return err;

    // Default sample rate divider
    err = setSampleRateDivider(0);
    if (err != Error::OK)
        return err;

    // Disable FIFO
    err = enableFIFO(false);
    if (err != Error::OK)
        return err;

    return Error::OK;
}

Error MPU6050::reset()
{
    return Error::OK;
}

Error MPU6050::setGyroRange(GyroRange range)
{
    return writeBits(
        reg::GYRO_CONFIG,
        4, // highest bit
        2, // number of bits
        static_cast<uint8_t>(range));
}

Error MPU6050::setAccelRange(AccelRange range)
{
    return writeBits(
        reg::ACCEL_CONFIG,
        4, // highest bit
        2, // number of bits
        static_cast<uint8_t>(range));
}

Error MPU6050::setDlpf(Dlpf dlpf)
{
    return writeBits(
        reg::CONFIG,
        2, // highest bit
        3, // number of bits
        static_cast<uint8_t>(dlpf));
}

Error MPU6050::setClockSource(ClockSource src)
{
    return writeBits(
        reg::PWR_MGMT_1,
        2, // highest bit
        3, // number of bits
        static_cast<uint8_t>(src));
}

Error MPU6050::setSampleRateDivider(uint8_t divider)
{
    return writeRegister(reg::SMPL_DIV, divider);
}

Error MPU6050::readRawAccel(Vector3i16 &accel)
{
    uint8_t buffer[6];

    Error err = readRegisters(reg::ACCEL_XOUT_H, buffer, sizeof(buffer));
    if (err != Error::OK)
    {
        return err;
    }

    // To Do -> Need to start returning Errors and changing bools to errors.
    accel.x = static_cast<int16_t>((buffer[0] << 8) | buffer[1]);
    accel.y = static_cast<int16_t>((buffer[2] << 8) | buffer[3]);
    accel.z = static_cast<int16_t>((buffer[4] << 8) | buffer[5]);

    return Error::OK;
}

Error MPU6050::readRawGyro(Vector3i16 &gyro)
{
    uint8_t buffer[6];

    Error err = readRegisters(reg::GYRO_XOUT_H, buffer, sizeof(buffer));
    if (err != Error::OK)
    {
        return err;
    }

    gyro.x = static_cast<int16_t>((buffer[0] << 8 | buffer[1]));
    gyro.y = static_cast<int16_t>((buffer[2] << 8 | buffer[3]));
    gyro.z = static_cast<int16_t>((buffer[4] << 8 | buffer[5]));

    return Error::OK;
}

Error MPU6050::readTemperature(int16_t &temperature)
{
    uint8_t buffer[2];

    Error err = readRegisters(reg::TEMP_OUT_H, buffer, sizeof(buffer));
    if (err != Error::OK)
    {
        return err;
    }

    temperature = (buffer[0] << 8) | buffer[1];

    return Error::OK;
}

Error MPU6050::readAll(IMUData &data)
{
    uint8_t buffer[14];

    Error err = readRegisters(reg::ACCEL_XOUT_H, buffer, sizeof(buffer));
    if (err != Error::OK)
    {
        return err;
    }

    data.accel.x = static_cast<int16_t>((buffer[0] << 8) | buffer[1]);
    data.accel.y = static_cast<int16_t>((buffer[2] << 8) | buffer[3]);
    data.accel.z = static_cast<int16_t>((buffer[4] << 8) | buffer[5]);
    data.temperature = static_cast<int16_t>((buffer[6] << 8) | buffer[7]);
    data.gyro.x = static_cast<int16_t>((buffer[8] << 8) | buffer[9]);
    data.gyro.y = static_cast<int16_t>((buffer[10] << 8) | buffer[11]);
    data.gyro.z = static_cast<int16_t>((buffer[12] << 8) | buffer[13]);

    return Error::OK;
}

Error MPU6050::enableFIFO(bool enable)
{
    uint8_t value;

    Error err = readRegister(reg::USER_CTRL, value);
    if (err != Error::OK)
    {
        return err;
    }

    if (enable)
        value |= (reg::FIFO_EN_BIT);
    else
        value &= ~(reg::FIFO_EN_BIT);
    err = writeRegister(reg::USER_CTRL, value);
    if (err != Error::OK)
    {
        return err;
    }

    if (enable)
    {
        value = 0;
        value |= reg::XG_FIFO_EN;
        value |= reg::YG_FIFO_EN;
        value |= reg::ZG_FIFO_EN;
        value |= reg::ACCEL_FIFO_EN;

        return writeRegister(reg::FIFO_EN, value);
    }
    else
    {
        return writeRegister(reg::FIFO_EN, 0);
    }
}

Error MPU6050::resetFIFO()
{
    uint8_t value;
    Error err = readRegister(reg::USER_CTRL, value);
    if (err != Error::OK)
    {
        return err;
    }

    value |= reg::FIFO_RESET;

    return writeRegister(reg::USER_CTRL, value);
}

Error MPU6050::getFIFOCount(uint16_t &count)
{
    uint8_t buffer[2];

    Error err = readRegisters(reg::FIFO_COUNT_H, buffer, 2);
    if (err != Error::OK)
    {
        return err;
    }

    count = (buffer[0] << 8) | buffer[1];

    return Error::OK;
}

Error MPU6050::readFIFO(uint8_t *data, uint16_t length)
{
    return readRegisters(reg::FIFO_R_W, data, length);
}