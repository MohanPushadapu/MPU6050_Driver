#pragma once
#include <cstdint>
#include <cstddef>
#include "errors.hpp"

class II2C 
{
    public: 
        virtual Error write(
            uint8_t address,
            uint8_t reg,
            const uint8_t* data,
            size_t length)=0;

        virtual Error read(
            uint8_t address, 
            uint8_t reg, 
            uint8_t* data,
            size_t length) = 0;
        
        virtual ~II2C() = default;
        };


class IDelay
{
public:
    virtual void delayMs(uint32_t ms)=0;
    virtual void delayUs(uint32_t us)=0;
    virtual ~IDelay()=default;
};