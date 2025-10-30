#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"
#include "iarduino_I2C_pH.h"

namespace esphome {
namespace ph_sensor {

class PH_Sensor : public PollingComponent, public i2c::I2CDevice {
 public:
  void setup() override;
  void update() override;
  void dump_config() override;
  
  void set_address(uint8_t address) { this->address_ = address; }
  void set_sensor(sensor::Sensor *sens) { this->sensor_ = sens; }  // New: for linking sensor output

 protected:
  iarduino_I2C_pH ph_;
  uint8_t address_ = 0x00;
  sensor::Sensor *sensor_{nullptr};  // Pointer to sensor for publishing
};

}  // namespace ph_sensor
}  // namespace esphome