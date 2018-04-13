#ifndef BASE_H
#define BASE_H

class Base {
  private:
    int encoderTicks;
  public:
    Base();
    /**
     * Move the base
     * @param left - speed of the left side
     * @param right - speed of the right side
     */
    void moveBase(int left, int right);
};

#endif
