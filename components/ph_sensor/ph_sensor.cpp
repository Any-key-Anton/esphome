#include "ph_sensor.h"
#include "esphome/core/log.h"

// Пространство имён: ph_sensor (без esphome::)
namespace ph_sensor {

static const char* const TAG = "ph_sensor";

void PHSensor::setup() {
  ESP_LOGCONFIG(TAG, "Setting up pH Sensor...");
  if (!this->ph_.begin(&this->get_wire())) {
    ESP_LOGE(TAG, "Failed to initialize pH sensor!");
    this->mark_failed();
    return;
  }
  if (this->address_ != 0x00) {
    this->ph_.changeAddress(this->address_);
  }
}

void PHSensor::dump_config() {
  ESP_LOGCONFIG(TAG, "pH Sensor:");
  ESP_LOGCONFIG(TAG, "  Address: 0x%02X", this->address_);
  ESP_LOGCONFIG(TAG, "  Update Interval: %d ms", this->update_interval_.to_milliseconds());
}

void PHSensor::update() {
  float ph_value = this->ph_.getPH();
  if (ph_value > 0.0f && ph_value <= 14.0f) {
    this->publish_state(ph_value);
    ESP_LOGD(TAG, "pH = %.3f", ph_value);
  } else {
    ESP_LOGW(TAG, "Invalid pH reading: %.3f", ph_value);
    // this->publish_state(NAN); // раскомментировать, если нужно отправлять NAN
  }
}

}  // namespace ph_sensor
