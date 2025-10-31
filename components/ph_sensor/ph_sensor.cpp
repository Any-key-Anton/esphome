#include "ph_sensor.h"
#include "esphome/core/log.h"

namespace ph_sensor { // <-- ВАЖНО: Это пространство имён

static const char *const TAG = "ph_sensor";

void PHSensor::setup() {
  ESP_LOGCONFIG(TAG, "Setting up pH Sensor...");
  // Убедитесь, что библиотека iarduino_I2C_pH поддерживает begin(Wire*)
  if (!this->ph_.begin(&this->get_wire())) {
    ESP_LOGE(TAG, "Failed to initialize pH sensor!");
    this->mark_failed();
    return;
  }
  // Если адрес не 0x00, меняем его
  if (this->address_ != 0x00) {
    this->ph_.changeAddress(this->address_);
  }
}

void PHSensor::dump_config() {
  ESP_LOGCONFIG(TAG, "pH Sensor:");
  ESP_LOGCONFIG(TAG, "  I2C Address: 0x%02X", this->address_);
  ESP_LOGCONFIG(TAG, "  Update Interval: %d ms", this->update_interval_.to_milliseconds());
  ESP_LOGCONFIG(TAG, "  pH Sensor: OK");
}

void PHSensor::update() {
  float ph_value = this->ph_.getPH();
  if (ph_value > 0 && ph_value <= 14.0f) {
    // Публикуем состояние напрямую через this->publish_state()
    this->publish_state(ph_value);
    ESP_LOGD(TAG, "Got pH: %.3f", ph_value);
  } else {
    ESP_LOGW(TAG, "Invalid pH reading: %.3f", ph_value);
    // this->publish_state(NAN); // Можно раскомментировать, если нужно отправлять NAN при ошибке
  }
}

}  // namespace ph_sensor
