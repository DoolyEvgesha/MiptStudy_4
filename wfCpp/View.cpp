#include <iostream>
#include <fstream>

#include "View.h"
#include "tui.h"

View::~View()
{
    inst = nullptr;
}

View * View::inst = nullptr;

View * View::get()
{
    if(inst != nullptr)
    {
        return inst;
    }

    inst = new Tui;
    return inst;
}

void View::setOnKey(KeyPressable * key)
{
    onkey_delegate = key;
}

void View::setModel(Game *g)
{
    game = g;
}



