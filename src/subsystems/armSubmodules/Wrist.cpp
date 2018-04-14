#include "main.h"

Wrist* Wrist::instance = 0;

Wrist::Wrist() {
}

void Wrist::move(int speed) {
  speed = threshold(speed);
  motorSet(wrist, speed);
}

Wrist* Wrist::getInstance() {
  if(instance == 0) {
    instance = new Wrist();
  }

  return instance;
}
