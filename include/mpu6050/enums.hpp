#pragma once
#include <cstdint> // C++

enum class GyroRange
{
    DPS250,
    DPS500,
    DPS1000,
    DPS2000
};

constexpr float gyroSensitivity(GyroRange range)
{
    switch (range)
    {
    case GyroRange::DPS250:
        return 131.0f;
    case GyroRange::DPS500:
        return 65.5f;
    case GyroRange::DPS1000:
        return 32.8f;
    case GyroRange::DPS2000:
        return 16.4f;
    }
    return 1.0f;
}

enum class AccelRange
{
    G2,
    G4,
    G8,
    G16
};

constexpr float accelSensitivity(AccelRange range)
{
    switch (range)
    {
    case AccelRange::G2:
        return 16384.0f;
    case AccelRange::G4:
        return 8192.0f;
    case AccelRange::G8:
        return 4096.0f;
    case AccelRange::G16:
        return 2048.0f;
    }
    return 1.0f;
}

enum class ClockSource
{
    INT8,
    XPLL,
    YPLL,
    ZPLL,
    PLL32,
    PLL16,
    RES,
    GEN
};

enum class Dlpf
{
    BW256,
    BW188,
    BW98,
    BW42,
    BW20,
    BW10,
    BW5
};