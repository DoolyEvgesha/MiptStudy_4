#include <iostream>
#include <fstream>

#include "View.h"
#include "tui.h"

View::~View()
{
    fout << "View dctor\n";
}

View * View::inst = nullptr;

//THE PROBLEM PROBABLY LIES HERE
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