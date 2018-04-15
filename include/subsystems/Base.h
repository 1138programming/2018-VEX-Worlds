#ifndef BASE_H
#define BASE_H

#include "main.h"

class Base {
  private:
    static Base* instance;
    Gyro gyro;
    Base();
  public:
    void moveBase(int left, int right);
    static Base* getInstance();
};

#endif
