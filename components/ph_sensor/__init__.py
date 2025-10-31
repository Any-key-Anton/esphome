import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, i2c
from esphome.const import (
    CONF_ID,
    DEVICE_CLASS_PH,
    STATE_CLASS_MEASUREMENT,
    UNIT_PH,
)

# Указываем, что этот компонент автоматически загружает базовый компонент sensor
AUTO_LOAD = ["sensor"]

# Указываем зависимости
DEPENDENCIES = ["i2c"]

# Создаём пространство имён для нашего компонента
# В C++ файле должно быть: namespace ph_sensor { ... }
ph_sensor_ns = cg.esphome_ns.namespace("ph_sensor")

# Определяем C++ класс
# Наследуемся от PollingComponent (для update_interval), Sensor и I2CDevice
PHSensor = ph_sensor_ns.class_(
    "PHSensor", cg.PollingComponent, sensor.Sensor, i2c.I2CDevice
)

# Определяем схему конфигурации
CONFIG_SCHEMA = sensor.sensor_schema( # Используем sensor.schema для создания сенсора
    PHSensor,                         # Указываем наш C++ класс
    unit_of_measurement=UNIT_PH,      # Единицы измерения
    accuracy_decimals=3,              # Знаки после запятой
    device_class=DEVICE_CLASS_PH,     # Класс устройства
    state_class=STATE_CLASS_MEASUREMENT, # Класс состояния
    icon="mdi:ph"                     # Иконка
).extend(                             # Добавляем общие настройки компонента
    cv.polling_component_schema("60s") # Настройки PollingComponent (update_interval)
).extend(                           # Добавляем настройки I2C
    i2c.i2c_device_schema(0x00)      # Схема I2C устройства, 0x00 по умолчанию
)

# Функция, генерирующая C++ код
async def to_code(config):
    # Создаём новую переменную C++ класса PHSensor
    var = cg.new_Pvariable(config[CONF_ID])

    # Регистрируем компонент (для setup, loop и т.д.)
    await cg.register_component(var, config)

    # Регистрируем его как sensor
    await sensor.register_sensor(var, config)

    # Регистрируем его как I2CDevice
    await i2c.register_i2c_device(var, config)
