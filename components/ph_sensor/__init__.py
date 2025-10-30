import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import (
    CONF_ID, CONF_ADDRESS, CONF_NAME,
    DEVICE_CLASS_PH, STATE_CLASS_MEASUREMENT, UNIT_PH
)

DEPENDENCIES = ['i2c']

ph_sensor_ns = cg.esphome_ns.namespace('ph_sensor')
PH_Sensor = ph_sensor_ns.class_('PH_Sensor', cg.PollingComponent)

CONFIG_SCHEMA = cv.COMPONENT_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(PH_Sensor),
    cv.Required(CONF_NAME): cv.string,
    cv.Optional(CONF_ADDRESS, default=0x00): cv.i2c_address,
    cv.Optional('update_interval', default='60s'): cv.update_interval,
    cv.Optional('accuracy_decimals', default=3): cv.int_range(min=0, max=5),
    cv.Optional('unit_of_measurement', default=UNIT_PH): cv.string,
    cv.Optional('icon', default="mdi:ph"): cv.icon,
    cv.Optional('device_class', default=DEVICE_CLASS_PH): cv.one_of(*sensor.DEVICE_CLASSES, lower=True),
    cv.Optional('state_class', default=STATE_CLASS_MEASUREMENT): cv.one_of(*sensor.STATE_CLASSES, lower=True),
})

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    sens = await sensor.new_sensor(config)
    cg.add(var.set_sensor(sens))
    if CONF_ADDRESS in config:
        cg.add(var.set_address(config[CONF_ADDRESS]))