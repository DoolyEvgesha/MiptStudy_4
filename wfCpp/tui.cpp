#include <iostream>
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <fstream>

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
    drawLineX(0, x, 0);
    drawLineY(0, y, 0);
    drawLineX(0, x, y);
    drawLineY(0, y, x);

    PR_COOR(__PRETTY_FUNCTION__, x, y);
}

void Tui::getWinSize()
{
    struct winsize ws;
    ioctl(1, TIOCGWINSZ, &ws);

    x = ws.ws_col;
    y = ws.ws_row;

    PR_COOR(__PRETTY_FUNCTION__, ws.ws_col, ws.ws_row);
    PR_COOR("Same function(x,y)", x, y);
}

static void onwinch(int x)
{
    fout << "On winch called\n";
    View * v = View::get();
    //v->getWinSize();
    v->draw();
    ///???????
    v->run();
//FJDSFKLKJFSNLDKNVSCKLSNSKADJNCSKLDKCNCDKSLCDKNXSKKCNK
    //PR_COOR(__PRETTY_FUNCTION__, x, y);
}

Tui::Tui()
{
    getWinSize();
  /*  struct winsize ws;
    ioctl(1, TIOCGWINSZ, &ws);

    x = ws.ws_col;
    y = ws.ws_row;
*/
    PR_COOR(__PRETTY_FUNCTION__, x, y);

    struct sigaction sa = {0};
    sa.sa_handler = onwinch;
    sigaction(SIGWINCH, &sa, 0);
}


void Tui::clearScreen()
{
    printf("\e[H\e[J");
}

Tui::~Tui()
{
    clearScreen();
    printf("Goodbye\n");
}

void Tui::run()
{
    PR_COOR(__PRETTY_FUNCTION__, x, y);
    getchar();

}

void Tui::gotoxy(int y, int x)
{
    printf("\e[%d;%dH", y, x);
}

