import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, i2c
from esphome.const import (
    CONF_ID,
    UNIT_PH,
    DEVICE_CLASS_PH,
    STATE_CLASS_MEASUREMENT,
)

AUTO_LOAD = ["sensor"]
DEPENDENCIES = ["i2c"]

# Пространство имён: "ph_sensor" (без esphome::)
ph_sensor_ns = cg.esphome_ns.namespace("ph_sensor")
PHSensor = ph_sensor_ns.class_("PHSensor", cg.PollingComponent, sensor.Sensor, i2c.I2CDevice)

CONFIG_SCHEMA = sensor.sensor_schema(
    PHSensor,
    unit_of_measurement=UNIT_PH,
    accuracy_decimals=3,
    device_class=DEVICE_CLASS_PH,
    state_class=STATE_CLASS_MEASUREMENT,
    icon="mdi:ph",
).extend(cv.polling_component_schema("60s")).extend(i2c.i2c_device_schema(0x00))


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await sensor.register_sensor(var, config)
    await i2c.register_i2c_device(var, config)
