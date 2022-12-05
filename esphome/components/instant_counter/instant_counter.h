#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"

namespace esphome {
namespace instant_counter {

class InstantCounter : public sensor::Sensor, public PollingComponent {
  public:
    binary_sensor::BinarySensor* input_;
    float rising_value_;
    float falling_value_;

    void set_input(binary_sensor::BinarySensor *input) { input_ = input; }
    void set_values(float rising_value, float falling_value) { rising_value_ = rising_value; falling_value_ = falling_value; }
    void dump_config() override;
    void setup() override;
    void update() override;
};

}  // namespace instant_counter
}  // namespace esphome
