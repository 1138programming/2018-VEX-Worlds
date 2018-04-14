#ifndef BASE_H
#define BASE_H

class Base {
  private:
    static Base* instance;
    Base();
  public:
    void moveBase(int left, int right);
    static Base* getInstance();
};

#endif
