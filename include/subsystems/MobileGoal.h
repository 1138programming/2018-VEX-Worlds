#ifndef MOBILEGOAL_H
#define MOBILEGOAL_H

class MobileGoal {
  private:
    int encoderTicks;
    static MobileGoal* instance;
    MobileGoal();
  public:
    void moveMobileGoal(int speed);
    void resetIME();
    int getIME();
    static MobileGoal* getInstance();
};

#endif
