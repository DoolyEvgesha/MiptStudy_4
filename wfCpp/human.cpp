#include <iostream>
#include <fstream>

#include "human.h"
#include "View.h"
#include "tui.h"

Human::Human()
{
    View::get()->setOnKey(this);
}

Human::~Human()
{
    std::cout << "Human dctr called\n";
}

void Human::onkey(int n)
{
    std::cout << "The key was pressed: " << (char)n << std::endl;
}