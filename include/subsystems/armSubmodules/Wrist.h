#ifndef WRIST_H
#define WRIST_H

class Wrist {
  private:
    static Wrist* instance;
    Wrist();
  public:
    void move(int speed);
    static Wrist* getInstance();
};

#endif
