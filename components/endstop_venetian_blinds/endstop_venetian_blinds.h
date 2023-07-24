#pragma once
#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/cover/cover.h"

namespace esphome {
namespace endstop_venetian_blinds {

class EndstopVenetianBlinds : public cover::Cover, public Component {
public:
  void setup() override;
  void loop() override;
  void dump_config() override;
  cover::CoverTraits get_traits() override;
  Trigger<> *get_open_trigger() const { return this->open_trigger; }
  Trigger<> *get_close_trigger() const { return this->close_trigger; }
  Trigger<> *get_stop_trigger() const { return this->stop_trigger; }
  void set_open_endstop(binary_sensor::BinarySensor *open_endstop) { this->open_endstop_ = open_endstop; }
  void set_close_endstop(binary_sensor::BinarySensor *close_endstop) { this->close_endstop_ = close_endstop; }
  void set_open_duration(uint32_t open) { this->open_duration = open; }
  void set_close_duration(uint32_t close) { this->close_duration = close; }
  void set_tilt_duration(uint32_t tilt) { this->tilt_duration = tilt; }
  void set_actuator_activation_duration(uint32_t actuator_activation) { this->actuator_activation_duration = actuator_activation; }
  void set_assumed_state(bool value) { this->assumed_state = value; }

protected:
  void control(const cover::CoverCall &call) override;
  bool is_open_() const { return this->open_endstop_->state; }
  bool is_closed_() const { return this->close_endstop_->state; }

  binary_sensor::BinarySensor *open_endstop_;
  binary_sensor::BinarySensor *close_endstop_;
  Trigger<> *open_trigger{new Trigger<>()};
  Trigger<> *close_trigger{new Trigger<>()};
  Trigger<> *stop_trigger{new Trigger<>()};
  uint32_t open_duration;
  uint32_t close_duration;
  uint32_t tilt_duration;
  uint32_t actuator_activation_duration;
  bool assumed_state{false};

private:
  uint32_t start_dir_time_{0};
  uint32_t last_recompute_time_{0};
  uint32_t last_publish_time_{0};
  uint32_t open_net_duration_;
  uint32_t close_net_duration_;
  uint32_t target_position_{0};
  uint32_t target_tilt_{0};
  int exact_position_{0};
  int exact_tilt_{0};

  void stop_prev_trigger_();
  bool is_at_target_() const;
  void start_direction_(cover::CoverOperation dir);
  void recompute_position_();

  Trigger<> *prev_command_trigger_{nullptr};
  cover::CoverOperation last_operation_{cover::COVER_OPERATION_OPENING};
};

} // namespace venetian_blinds
} // namespace esphome
