#include <iostream>
#include <fstream>
#include <cstring>
#include "View.h"
#include "tui.h"

View * View::inst_ = nullptr;

View::~View()
{ inst_ = nullptr; }

View * View::get()
{
    if(inst_ != nullptr)
    {
        return inst_;
    }

    inst_ = new Tui;
    return inst_;
}

/*View * View::get(const char *type)
{
    if(!strcmp(type, "tui"))
    {
        if(inst_)
            return inst_;
        inst_ = new Tui;
        return inst_;
    }
    else
    {
        fout << "Cannot recognise type" << __PRETTY_FUNCTION__;
        return nullptr;
    }
}*/