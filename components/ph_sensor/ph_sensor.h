#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"
// #include "iarduino_I2C_pH.h" // Включите, если файл лежит внутри папки компонента
#include "iarduino_I2C_pH.h" // Или так, если файл доступен в пути сборки

namespace ph_sensor { // <-- ВАЖНО: Это пространство имён

class PHSensor : public esphome::PollingComponent, public esphome::sensor::Sensor, public esphome::i2c::I2CDevice {
 public:
  void setup() override;
  void dump_config() override;
  void update() override;

 protected:
  iarduino_I2C_pH ph_;
};

}  // namespace ph_sensor
