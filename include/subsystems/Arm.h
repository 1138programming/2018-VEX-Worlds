#ifndef ARM_H
#define ARM_H

class Arm {
  private:
    int encoderTicks;
    static Arm* instance;
    Arm();
  public:
    void moveWrist(int speed);
    void moveFourBar(int speed);
    static Arm* getInstance();
};

#endif
