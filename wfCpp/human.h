#ifndef HUMAN_H
#define HUMAN_H

#include "control.h"
#include "keypressable.h"

class Human : public Control, KeyPressable{
public:
    Human               (Snake *, Game *);
    ~Human              ();
    void onkey          (int);
    Game *              game;
};

#endif //HUMAN_H
