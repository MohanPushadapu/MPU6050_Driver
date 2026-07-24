#include "arduino.hpp"

Arduino::Arduino(TwoWire &wire) : wire_(wire)
{
}

Error Arduino::begin()
{
    wire_.begin();

    return Error::OK;
}

Error Arduino::write(
    uint8_t address,
    uint8_t reg,
    const uint8_t *data,
    size_t length)
{
    wire_.beginTransmission(address);

    wire_.write(reg);
    wire_.write(data, length);
    uint8_t result = wire_.endTransmission();

    switch (result)
    {
    case 0:
        return Error::OK;
    case 2:
    case 3:
        return Error::Nack;
    case 4:
        return Error::BusError;
    default:
        return Error::Undefined;
    }
}

Error Arduino::read(
    uint8_t address,
    uint8_t reg,
    uint8_t *data,
    size_t length)
{

    wire_.beginTransmission(address);
    wire_.write(reg);
    uint8_t result = wire_.endTransmission(false);
    if (result != 0)
    {
        switch (result)
        {
        case 2:
        case 3:
            return Error::Nack;
        case 4:
            return Error::BusError;
        default:
            return Error::Undefined;
        }
    }

    size_t received =
        wire_.requestFrom(
            address,
            static_cast<uint8_t>(length));

    if (received != length)
    {
        return Error::Timeout;
    }
    for (size_t i = 0; i < length; ++i)
    {
        data[i] = wire_.read();
    }
    return Error::OK;
}