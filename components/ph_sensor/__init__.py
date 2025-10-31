import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, i2c
from esphome.const import (
    CONF_ID,
    CONF_ADDRESS,
    CONF_NAME,
    DEVICE_CLASS_PH,
    STATE_CLASS_MEASUREMENT,
    UNIT_PH,
)

# Указываем, что этот компонент автоматически загружает базовый компонент sensor
AUTO_LOAD = ["sensor"]

# Указываем зависимости
DEPENDENCIES = ["i2c"]

# Создаём пространство имён для нашего компонента
# ИСПРАВЛЕНО: теперь соответствует namespace esphome { namespace ph_sensor { ... }}
ph_sensor_ns = cg.esphome_ns.namespace("esphome::ph_sensor")

# Определяем C++ класс
# Наследуемся от PollingComponent (для update_interval), Sensor и I2CDevice
PHSensor = ph_sensor_ns.class_(
    "PHSensor", cg.PollingComponent, sensor.Sensor, i2c.I2CDevice
)

# Определяем схему конфигурации
CONFIG_SCHEMA = sensor.sensor_schema(
    PHSensor,
    unit_of_measurement=UNIT_PH,
    accuracy_decimals=3,
    device_class=DEVICE_CLASS_PH,
    state_class=STATE_CLASS_MEASUREMENT,
    icon="mdi:ph"
).extend(
    cv.polling_component_schema("60s")
).extend(
    i2c.i2c_device_schema(0x00)
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await sensor.register_sensor(var, config)
    await i2c.register_i2c_device(var, config)
