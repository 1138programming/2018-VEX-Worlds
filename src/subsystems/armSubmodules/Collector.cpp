#include "main.h"

Collector* Collector::instance = 0;

Collector::Collector() {
  collectorMotor = Motor::getMotor(collectorPort);
}

void Collector::move(int speed) {
  speed = range(speed);
  collectorMotor->setSpeed(speed);
}

Collector* Collector::getInstance() {
  if (instance == 0) {
    instance = new Collector();
  }

  return instance;
}
