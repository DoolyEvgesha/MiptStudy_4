#include <iostream>
#include <fstream>

#include "View.h"
#include "tui.h"
#include <unistd.h>

int main() {
    //Tui t;
    View * v = View::get();
    v->draw();

    int c = '*';
    do {
        //v->run();
        std::cout << "C = " << c << "@" << std::endl;
        if(pisdec) {
            pisdec = 0;
        }
        c = getchar();
        std::cout << "C2 = " << c << "#" << std::endl;
    } while(c == '*');


    delete v;
    return 0;
}