#include "ph_sensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace ph_sensor {

static const char *const TAG = "ph_sensor";

void PHSensor::setup() {
  ESP_LOGCONFIG(TAG, "Setting up pH Sensor...");
  // Передаём указатель на Wire-объект из I2CDevice
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
  LOG_I2C_DEVICE(this);
  LOG_SENSOR("  ", "pH", this); // Добавляем логирование сенсора
  LOG_UPDATE_INTERVAL(this);
}

void PHSensor::update() {
  float ph_value = this->ph_.getPH();
  if (ph_value > 0 && ph_value <= 14.0f) {
    // Публикуем состояние напрямую через this->publish_state()
    this->publish_state(ph_value);
    ESP_LOGD(TAG, "Got pH: %.3f", ph_value);
  } else {
    ESP_LOGW(TAG, "Invalid pH reading: %.3f", ph_value);
    // Можно опубликовать NAN, чтобы показать недостоверное значение
    // this->publish_state(NAN);
  }
}

}  // namespace ph_sensor
}  // namespace esphome
