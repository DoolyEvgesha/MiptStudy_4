#include <iostream>
#include <fstream>

#include "View.h"
#include "tui.h"
#include "human.h"
#include "game.h"
#include "ai.h"
#include <unistd.h>

int main() {
    View * v = View::get();
    Game g;
    Snake s;

    Snake s_ai;
    Ai ai(&s_ai, &g);

    Human h(&s, &g);
    g.add(&s);

    g.controls.push_back(&ai);
    g.add(&s_ai);

    v->setModel(&g);
    v->draw();
    v->run();

    delete v;
    return 0;
}
