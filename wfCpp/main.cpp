#include <iostream>
#include <fstream>

#include "View.h"
#include "tui.h"
#include "human.h"
#include <unistd.h>

int main() {
    View * v = View::get();
    Human h;

    v->draw();
    v->run();

    delete v;
    return 0;
}
