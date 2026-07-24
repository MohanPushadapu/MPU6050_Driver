#pragma once
#include <cstdint>   // C++

enum class GyroRange {
    DPS250,
    DPS500,
    DPS1000,
    DPS2000
};

enum class AccelRange
{
    G2,
    G4,
    G8,
    G16
};

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