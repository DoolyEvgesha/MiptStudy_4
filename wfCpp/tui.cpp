#include <iostream>
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <fstream>
#include <termios.h>
#include <unistd.h>
#include <functional>

using namespace std::placeholders;

#include "tui.h"

void Tui::drawLineX(int start, int length, int y)
{
    for(int i = start; i < start + length; ++i)
    {
        gotoxy(i, y);
        printf("*");
    }
}

void Tui::drawLineY(int start, int length, int x)
{
    for(int i = start; i < start + length; ++i)
    {
        gotoxy(x, i);
        printf("*");
    }
}

//gonna draw here snakes
void Tui::draw()
{
    clearScreen();
    getWinSize();

    drawLineX(0, x, 0);
    drawLineY(0, y, 0);
    drawLineX(0, x, y);
    drawLineY(0, y, x);

    game->paint(std::bind(&View::snakePainter, this, _1, _2));
    fflush(stdout);

}

void Tui::getWinSize()
{
    struct winsize ws;
    ioctl(1, TIOCGWINSZ, &ws);

    x = ws.ws_row;
    y = ws.ws_col;
}

void onwinch(int x)
{
    View * v = View::get();

    v->draw();
}

Tui::Tui():
    x(0),
    y(0)
{
    setbuf(stdout, NULL);

    struct sigaction sa = {0};
    sa.sa_handler = onwinch;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGWINCH, &sa, 0);

    struct termios a;
    tcgetattr(0, &a);
    old = a;
    cfmakeraw(&a);
    tcsetattr(0, TCSAFLUSH, &a);
}


void Tui::clearScreen()
{
    printf("\e[H\e[J");
}

Tui::~Tui()
{
    tcsetattr(0, TCSAFLUSH, &old);

    clearScreen();
    printf("Goodbye\n");
}

void Tui::run()
{
    while(1){
        int c;
        gotoxy(x/2, y/2);
        c = getchar();

        if(c == 'q')
            break;

        if(c != -1)
        {
            if(onkey_delegate != nullptr)
                onkey_delegate->onkey(c);
        }
    }

}

void Tui::gotoxy(int x, int y)
{
    printf("\e[%d;%dH", x, y);
}

void Tui::snakePainter(Coord c, Dir d)
{
    gotoxy(c.first, c.second);
    putchar("^v><#"[d]);
}