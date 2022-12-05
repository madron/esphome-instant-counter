#include "instant_counter.h"
#include "esphome/core/log.h"

namespace esphome {
namespace instant_counter {

static const char *const TAG = "instant_counter";

void InstantCounter::dump_config() {
  ESP_LOGCONFIG(TAG, "InstantCounter");
  ESP_LOGCONFIG(TAG, "  rising_value: %f", this->rising_value_);
  ESP_LOGCONFIG(TAG, "  falling_value: %f", this->falling_value_);
}

void InstantCounter::setup() {
  this->publish_state(0);
  this->input_->add_on_state_callback([this](bool state) {
    ESP_LOGV(TAG, "Input state: %d", state);
    if (state == 1 and this->rising_value_ > 0) this->publish_state(this->get_raw_state() + this->rising_value_);
    if (state == 0 and this->falling_value_ > 0) this->publish_state(this->get_raw_state() + this->falling_value_);
  });
}

void InstantCounter::update() {
  this->publish_state(this->get_raw_state());
}

}  // namespace instant_counter
}  // namespace esphome
