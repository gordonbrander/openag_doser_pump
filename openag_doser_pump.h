#ifndef OPENAG_DOSER_PUMP_H
#define OPENAG_DOSER_PUMP_H

#include "Arduino.h"
#include <std_msgs/Bool.h>
#include <openag_module.h>

class DoserPump : public Module {
  public:
    // Constructor
    DoserPump(int pin, bool is_active_low, uint8_t eeprom_addr);

    // Public functions
    void begin();
    void update();
    void set_cmd(std_msgs::Float32 cmd);

  private:
    // Private variables
    int _pin;
    bool _is_active_low;
    uint8_t _eeprom_addr;
    _rate100 = 0.0019;
    _rate1000 = 0.0015;
};

#endif
