#include "main.h"

Collector* Collector::instance = 0;

Collector::Collector() {

}

void Collector::move(int speed) {
  speed = range(speed);
  motorSet(collectorPort, speed);
}

Collector* Collector::getInstance() {
  if (instance == 0) {
    instance = new Collector();
  }

  return instance;
}
