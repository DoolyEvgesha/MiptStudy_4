#ifndef CONTROL_H
#define CONTROL_H

#include "game.h"

class Control{
public:
    explicit Control(Snake * s){ snake = s; };
    Snake * snake;
};

#endif //CONTROL_H
