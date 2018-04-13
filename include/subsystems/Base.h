#ifndef BASE_H
#define BASE_H

class Base {
  private:
    int encoderTicks;
    static Base* instance;
    Base();
  public:
    void moveBase(int left, int right);
    static Base* getInstance();
};

#endif
