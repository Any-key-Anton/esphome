#include "ph_sensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace ph_sensor {

static const char *const TAG = "ph_sensor";

void PH_Sensor::setup() {
  ESP_LOGCONFIG(TAG, "Setting up pH Sensor...");
  if (!this->ph_.begin(&this->parent_->get_wire())) {
    ESP_LOGE(TAG, "Failed to initialize pH sensor!");
    this->mark_failed();
    return;
  }
  if (this->address_ != 0) {
    this->ph_.changeAddress(this->address_);
  }
}

void PH_Sensor::dump_config() {
  ESP_LOGCONFIG(TAG, "pH Sensor:");
  LOG_I2C_DEVICE(this);
  LOG_UPDATE_INTERVAL(this);
}

void PH_Sensor::update() {
  float ph_value = this->ph_.getPH();
  if (ph_value > 0 && ph_value <= 14.0f) {
    if (this->sensor_ != nullptr) {
      this->sensor_->publish_state(ph_value);
    }
    ESP_LOGD(TAG, "Got pH: %.3f", ph_value);
  } else {
    ESP_LOGW(TAG, "Invalid pH reading: %.3f", ph_value);
  }
}

}  // namespace ph_sensor
}  // namespace esphome