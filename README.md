# esphome-instant-counter
Instant counter for ESPHome

The sensor publishes the counter value every update_interval and as soon as the value changes.

```yaml
# Example configuration entry
external_components:
  - source: github://madron/esphome-instant-counter
    components:
      - instant_counter


binary_sensor:
  - platform: gpio
    id: water_pulse
    pin:
      number: GPIO32


sensor:
  - platform: instant_counter
    name: water_volume
    input: water_pulse
    rising_value: 0.5
    falling_value: 0.5
    unit_of_measurement: l
    accuracy_decimals: 1
    icon: mdi:water
```


## Configuration variables:
  - **input** (**Required**): A binary sensor id
  - **rising_value** (Optional): The value to add to the counter when the input binary sensor rises from 0 to 1. Defaults to 1.
  - **falling_value** (Optional): The value to add to the counter when the input binary sensor falls from 1 to 0. Defaults to 0.
  - **update_interval** (Optional, Time): The interval to check the sensor. Defaults to 60s.
