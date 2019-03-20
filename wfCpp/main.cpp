#include <iostream>
#include <fstream>

#include "View.h"
#include "tui.h"

int main() {
    //Tui t;
    View * v = View::get();

    v->draw();
    v->run();

    delete v;
    return 0;
}