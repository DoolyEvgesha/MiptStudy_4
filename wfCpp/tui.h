#ifndef TUI_H
#define TUI_H

#include "View.h"

#define PR_COOR(FUNC, x, y)                                 \
    do{                                                     \
        fout << FUNC << ": \t\t" << x << " " << y << std::endl; \
    }while(0)

static std::ofstream fout("logFile.txt");

class Tui:public View{

private:
    int x;
    int y;

public:
    Tui();
    ~Tui();

    void draw();
    void getWinSize();
    void drawLineY(int, int, int);
    void drawLineX(int, int, int);
    void gotoxy(int, int);//moves to the certain possition
    void run();
    void clearScreen();
};

#endif
//man ioctl_tty

//sa.sa ... = onwigch;
//sigaction(SIGWINSZ, &sa);
//static onwich(int x)
//{}