#ifndef _SHAFT_ENCODER_H
#define _SHAFT_ENCODER_H

#include "main.h"
#include "abstractBaseClasses/Sensor.h"

class ShaftEncoder: public Sensor {
  private:
    Encoder encoderInstance;
  public:
    int getSensorValue();
    ShaftEncoder(int topPort, int bottomPort);
};

#endif
