#include <iostream>
#include <fstream>

#include "game.h"
#include "human.h"
#include "View.h"
#include "tui.h"

Human::Human(Snake * s):Control(s)
{
    View::get()->setOnKey(this);
}

Human::~Human()
{
    std::cout << "Human dctr called\n";
}

void Human::onkey(int n)
{
    printf("key pressed = %d ", n);

    switch (n) {
        case 'd':
            snake->direction = RIGHT;
            break;
        case 'a':
            snake->direction = LEFT;
            break;
        case 'w':
            snake->direction = UP;
            break;
        case 's':
            snake->direction = DOWN;
            break;
    }

    View::get()->draw();
}