#pragma once

enum class I2CResult 
{
    Ok, 
    BusError,
    Timeout, 
    Nack, 
    Undefined
};

enum class Error {
    OK, 
    BusError,
    InvalidParameter,
    DeviceNotFound,
    Timeout,
    Nack,
    Undefined
};