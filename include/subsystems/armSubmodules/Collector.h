#ifndef COLLECTOR_H
#define COLLECTOR_H

#include "main.h"

class Collector {
  private:
    static Collector* instance;
    Motor* collectorMotor;
    Collector();
  public:
    void move(int speed);
    static Collector* getInstance();
};

#endif
