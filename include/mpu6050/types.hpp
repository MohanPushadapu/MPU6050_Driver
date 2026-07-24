#pragma once
#include <cstdint>   // C++

struct Vector3f
{
    float x;
    float y;
    float z;
};

struct Vector3i16
{
    int16_t x;
    int16_t y;
    int16_t z;
};

struct IMUData {
    Vector3i16 accel;
    Vector3i16 gyro;
    int16_t temperature;
    // uint64_t timestamp_us;
};

struct Interrupt
{
    // To-Do
};


struct Temperature
{
    float temperature;
};

