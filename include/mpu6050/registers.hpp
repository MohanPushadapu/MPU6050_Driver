#pragma once
#include <cstdint>      //C++

namespace reg 
{

/*
Parameters: 
SMPLRT_DIV          Sample rate is determined by dividing the gyroscope output by this value. 
*/
constexpr uint8_t SMPL_DIV = 0x19;

/*
Parameters: 
    EST_SYNC_SET    Configures the FSYNC pin sampling.
    DLPF_CFG        Configures the DLPF setting.
*/
constexpr uint8_t CONFIG = 0x1A;


/*
Parameters:
    XG_ST           Setting this bit causes X axis gyroscope to perform self test
    YG_ST           Y axis self test
    ZG_ST           Z axis self test
    FS_SEL          Selects the full scale range of gyroscopes.
 */
constexpr uint8_t GYRO_CONFIG = 0x1B;

/*
Parameters:
    XA_ST           Bit 7 -> X-axis accelerometer self test
    YA_ST           Bit 6 -> Y-axis self test
    ZA_ST           Bit 5 -> Z-axis self test
    AFS_SEL         Bit 4-3 -> Full scale range of accelerometers.
 */
constexpr uint8_t ACCEL_CONFIG = 0x1C;

/*
Parameters:
    MOR_THR         Bit 7-0 -> Motion detection threshold.
 */
constexpr uint8_t MOT_THR = 0x1F;

/*
Parameters:
    TEMP_FIFO_EN        When set to 1, enables TEMP_OUT_H and TEMP_OUT_L to be written into FIFO buffer.
    XG_FIFO_EN          Bit 6 -> enables GYRO_XOUT to be written into the FIFO buffer.
    YG_FIFO_EN          Bit 5 -> enables GYRO_YOUT to be written into FIFO buffer.
    ZG_FIFO_EN          Bit 4 -> enables GYRO_ZOUT to be written into FIFO buffer.
    ACCEL_FIFO_EN       Bit 3 -> enables all ACCELL to be written into FIFO buffer.
    SLV2_FIFO_EN        Bit 2 -> enables EST_SENS_DATA registers associated with slave 2 to be written into the FIFO buffer. 
    SLV1_FIFO_EN        Bit 1 -> enables EST_SENS_DATA registers associated with slave 1 to be written into the FIFO buffer. 
    SLV0_FIFO_EN        Bit 0 -> enables EST_SENS_DATA registers associated with slave 0 to be written into the FIFO buffer. 
 */
constexpr uint8_t FIFO_EN = 0x23;
constexpr uint8_t TEMP_FIFO_EN  = 1 << 7;
constexpr uint8_t XG_FIFO_EN    = 1 << 6;
constexpr uint8_t YG_FIFO_EN    = 1 << 5;
constexpr uint8_t ZG_FIFO_EN    = 1 << 4;
constexpr uint8_t ACCEL_FIFO_EN = 1 << 3;
constexpr uint8_t SLV2_FIFO_EN  = 1 << 2;
constexpr uint8_t SLV1_FIFO_EN  = 1 << 1;
constexpr uint8_t SLV0_FIFO_EN  = 1 << 0;

/*
Parameters:
    MUL_MST_EN          Bit 7 -> when set to 1, enables multi-master capability.
    WAIT_FOR_ES         Bit 6 -> Delays the data ready interrupt until External Sensor data from the Slave devices have been loaded into the EXT_SENS_DATA registers.
    SLV3_FIFO_EN        Bit 5 -> EXT_SENS_DATA registers associated with Slave 3 to be written into the FIFO.
    I2C_MST_P_NSR       Bit 4 -> Controls the I2C Master's transition from one slave read to the next slave read. 
                        Bit->0 there is a researt between reads.
                        Bit->1 there is a stop and start making the beginning of the next read. 
    I2C_MST_CLK         Bit 3-0 -> I2C master clock speed divider. 
 */
constexpr uint8_t I2C_MST_CTRL = 0x24;

/*
Parameters:
    ACCEL_XOUT          16 Bit -> Stores most recent X axis accelerometer measurment.
    ACCEL_YOUT          16 Bit -> Stores most recent Y axis accelerometer measurment.
    ACCEL_ZOUT          16 Bit -> Stores most recent Z axis accelerometer measurment.
 */
constexpr uint8_t ACCEL_XOUT_H = 0x3B;
constexpr uint8_t ACCEL_XOUT_L = 0x3C;
constexpr uint8_t ACCEL_YOUT_H = 0x3D;
constexpr uint8_t ACCEL_YOUT_L = 0x3E;
constexpr uint8_t ACCEL_ZOUT_H = 0x3F;
constexpr uint8_t ACCEL_ZOUT_L = 0x40;

/*
Parameters:
    TEMP_OUT            Stores most recent temperature sensor measurement.
 */
constexpr uint8_t TEMP_OUT_H = 0x41;
constexpr uint8_t TEMP_OUT_L = 0x42;

/*
Parameters:
    GYRO_XOUT           most recent X-axis gyroscope measurement.
    GYRO_YOUT           most recent Y-axis gyroscope measurement.
    GYRO_ZOUT           most recent Z-axis gyroscope measurement.
 */
constexpr uint8_t GYRO_XOUT_H = 0x43;
constexpr uint8_t GYRO_XOUT_L = 0x44;
constexpr uint8_t GYRO_YOUT_H = 0x45;
constexpr uint8_t GYRO_YOUT_L = 0x46;
constexpr uint8_t GYRO_ZOUT_H = 0x47;
constexpr uint8_t GYRO_ZOUT_L = 0x48;


/*
Parameters:
    FIFO_EN             Bit 6 -> When set to 1 FIFO is enabled. 
    I2C_MUST_EN         Bit 5 -> When set to 1 I2C Master mode is enabled.
    I2C_IF_DIS          Bit 4 -> Always 0 
    FIFO_RESET          Bit 2 -> When set to 1 resets FIFO buffer when FIFO_EN is set to 0. Automatically resets to 0 once buffer is reset.
    I2C_MST_RESET       Bit 1 -> When set to 1 resets I2C Master when I2C_MST_EN is set to 0. Automatically clears to 0 after reset triggered.
    SIG_COND_RESET      Bit 0 -> When set to 1 resets the signals paths for all sensors. Automatically clears to 0 after reset triggered. 
 */
constexpr uint8_t USER_CTRL = 0x6A;
constexpr uint8_t FIFO_EN_BIT = 1 << 6;
constexpr uint8_t I2C_MUST_EN = 1 << 5;
constexpr uint8_t I2C_IF_DIS = 1 << 4;
constexpr uint8_t FIFO_RESET = 1 << 2;
constexpr uint8_t I2C_MST_RESET = 1 << 1;
constexpr uint8_t SIG_COND_RESET = 1;





/*
Parameters:
    DEVICE_RESET        Bit 7 -> When set to 1, resets all internal registers.
    SLEEP               Bit 6 -> When set to 1, goes to sleep. 
    CYCLE               Bit 5 -> Will cycle between sleep mode and waking up to take a sample of data from sensors.
    TEMP_DIS            Bit 3 -> Disables the temperature sensor.
    CLKSEL              Specifies the clock source of the device.

 */
constexpr uint8_t PWR_MGMT_1 = 0x6B;
constexpr uint8_t DEVICE_RESET = 1 << 7;
constexpr uint8_t SLEEP = 1<< 6;
constexpr uint8_t CYCLE = 1<< 5;
constexpr uint8_t TEMP_DIS = 1<< 3;

/*
Parameters:
    ToDo
 */
constexpr uint8_t PWR_MGMT_2 = 0x6C;

/*
Parameters:
   ToDo
 */
constexpr uint8_t FIFO_COUNT_H = 0x72;
constexpr uint8_t FIFO_COUNT_L = 0x73;

constexpr uint8_t FIFO_R_W = 0x74;

constexpr uint8_t WHO_AM_I = 0x75;

}