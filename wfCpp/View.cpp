#include <iostream>
#include <fstream>

#include "View.h"
#include "tui.h"

View::~View()
{
    fout << "View dctor\n";
}

View * View::inst;

//THE PROBLEM PROBABLY LIES HERE
View * View::get()
{
    if(inst)
    {
        fout << "return inst\n";
        return inst;
    }

    fout << "return new Tui\n";
    return new Tui;
}