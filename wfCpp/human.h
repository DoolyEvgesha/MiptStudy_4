#ifndef HUMAN_H
#define HUMAN_H

#include "control.h"
#include "keypressable.h"

class Human : public Control, KeyPressable{
public:
    Human               (Snake *);
    ~Human              ();
    void onkey          (int);

};

#endif //HUMAN_H
