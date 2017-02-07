#include "openag_doser_pump.h"

DoserPump::DoserPump(int pin, bool is_active_low, uint8_t eeprom_addr) {
  _pin = pin;
  _is_active_low = is_active_low;
  _eeprom_addr= eeprom_addr;
  status_level = OK;
  status_code = CODE_OK;
  status_msg = "";
}

void DoserPump::begin() {
  pinMode(_pin, OUTPUT);
  if (_is_active_low) {
    digitalWrite(_pin, HIGH);
  }
  else {
    digitalWrite(_pin, LOW);
  }
}

void DoserPump::update() {}

void DoserPump::void set_cmd(std_msgs::Float32 cmd) {
  float prev_cmd;
  prev_cmd = EEPROM.get(_eeprom_addr, prev_cmd);
  if (cmd != prev_cmd) {

    // Update local memory
    EEPROM.put(_eeprom_addr, cmd);

    // Determine dosing rate
    float rate = 0; // ml/ms
    if (cmd < 100 * _rate100) {
      rate = _rate100;
    }
    else if (cmd < 1000 * _rate1000) {
      float slope = (_rate1000 - _rate100) / (_rate1000 * 1000 - _rate100 * 100);
      rate = _rate100 + slope * (cmd - _rate100 * 100);
    }
    else {
      rate = _rate1000;
    }

    // Set pump on for duration then turn off
    float duration = cmd / rate;
    if (_is_active_low) {
      digitalWrite(_pin, LOW);
      delay(duration);
      digitalWrite(_pin, HIGH);
    }
    else {
      digitalWrite(_pin, HIGH);
      delay(duration);
      digitalWrite(_pin, LOW);
    }
  }
}
