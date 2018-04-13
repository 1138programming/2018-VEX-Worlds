#ifndef MOBILEGOAL_H
#define MOBILEGOAL_H

class MobileGoal {
  private:
    int encoderTicks;
    static MobileGoal* instance;
    MobileGoal();
  public:
    void moveMobileGoal(int speed);
    static MobileGoal* getInstance();
};

#endif
