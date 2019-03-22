#include <iostream>
#include <fstream>

#include "View.h"
#include "tui.h"

View::~View()
{
    fout << "View dctor\n";
    inst = nullptr;
}

View * View::inst = nullptr;

View * View::get()
{
    if(inst != nullptr)
    {
        fout << "return inst\n";
        return inst;
    }

    fout << "return new Tui\n";
    inst = new Tui;
    return inst;
}

void View::setOnKey(KeyPressable * key)
{
    onkey_delegate = key;
}

