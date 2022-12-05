import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor, sensor
from esphome.const import CONF_ID, CONF_INPUT, STATE_CLASS_TOTAL_INCREASING

CONF_RISING_VALUE = 'rising_value'
CONF_FALLING_VALUE = 'falling_value'


instant_counter_ns = cg.esphome_ns.namespace("instant_counter")
InstantCounter = instant_counter_ns.class_(
    "InstantCounter", sensor.Sensor, cg.Component
)


INCREASING_SENSOR_SCHEMA = sensor.sensor_schema(
    state_class=STATE_CLASS_TOTAL_INCREASING,
)


CONFIG_SCHEMA = INCREASING_SENSOR_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(InstantCounter),
        cv.Required(CONF_INPUT): cv.use_id(binary_sensor.BinarySensor),
        cv.Optional(CONF_RISING_VALUE, default=1): cv.positive_float,
        cv.Optional(CONF_FALLING_VALUE, default=0): cv.positive_float,
    }
).extend(cv.polling_component_schema('60s'))


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await sensor.register_sensor(var, config)
    input = await cg.get_variable(config[CONF_INPUT])
    cg.add(var.set_input(input))
    cg.add(var.set_values(config[CONF_RISING_VALUE], config[CONF_FALLING_VALUE]))
