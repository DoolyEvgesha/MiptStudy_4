#include <iostream>
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <fstream>
#include <termios.h>
#include <unistd.h>

#include "tui.h"
void Tui::drawLineX(int start, int length, int y)
{
    for(int i = start; i < start + length; ++i)
    {
        gotoxy(y, i);
        printf("*");
    }
}

void Tui::drawLineY(int start, int length, int x)
{
    for(int i = start; i < start + length; ++i)
    {
        gotoxy(i, x);
        printf("*");
    }
}

void Tui::draw()
{
    clearScreen();
    getWinSize();

    drawLineX(0, x, 0);
    drawLineY(0, y, 0);
    drawLineX(0, x, y);
    drawLineY(0, y, x);

    fflush(stdout);

    PR_COOR(__PRETTY_FUNCTION__, x, y);
}

void Tui::getWinSize()
{
    struct winsize ws;
    ioctl(1, TIOCGWINSZ, &ws);

    x = ws.ws_col;
    y = ws.ws_row;

    PR_COOR(__PRETTY_FUNCTION__, ws.ws_col, ws.ws_row);
}

static void onwinch(int x)
{
    fout << "On winch called\n";
    View * v = View::get();

    v->draw();
}

Tui::Tui():
    x(0),
    y(0)
{
//tc get attr(0, &a)
//tc set attr(0, TCSAFLUSH, &a) //the terminal doesn't wait for Enter
//cf make raw(&a)
//sigaction(SIGINT, SIGSEGV)

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
    fout << "clearScreen\n";
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
    PR_COOR(__PRETTY_FUNCTION__, x, y);

    while(1){
        int c;
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

void Tui::gotoxy(int y, int x)
{
    printf("\e[%d;%dH", y, x);
}

