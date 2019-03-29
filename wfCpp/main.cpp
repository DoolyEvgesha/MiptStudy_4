#include <iostream>
#include <fstream>

#include "View.h"
#include "tui.h"
#include "human.h"
#include "game.h"
#include <unistd.h>

int main() {
    Game g;
    View * v = View::get();
    Human h;

    v->setModel(&g);
    v->draw();
    v->run();

    delete v;
    return 0;
}
