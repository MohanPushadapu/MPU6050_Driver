#include "mpu6050/mpu6050.hpp"

#include "arduinoi2c.hpp"

// #include "ports/arduino/arduinoi2c.hpp"



ArduinoI2C bus(Wire);
MPU6050 imu(bus);

void setup()
{
  Serial.begin(115200);
  delay(1000);
  esp_log_level_set("*", ESP_LOG_INFO);
  Wire.begin();
  ESP_LOGI("main", "Log successful");

  auto err = imu.begin();
  ESP_LOGI("main", "Log successful part 2");

  if (err != Error::OK)
  {
    Serial.println("MPU6050 init failed");
    while (true)
    {
      delay(1000);
    }
  }
  Serial.println("MPU6050 init success");
}

void loop()
{

  Vector3i16 accel;
  Vector3i16 gyro;

  imu.readRawAccel(accel);
  imu.readRawGyro(gyro);
  Serial.print("          Gyro: ");
  Serial.print(gyro.x);
  Serial.print(", ");
  Serial.print(gyro.y);
  Serial.print(", ");
  Serial.print(gyro.z);
  Serial.print("          Accel: ");
  Serial.print(accel.x);
  Serial.print(", ");
  Serial.print(accel.y);
  Serial.print(", ");
  Serial.println(accel.z);

  delay(100);
}