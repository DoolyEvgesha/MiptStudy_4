#ifndef TUI_H
#define TUI_H

#include <termios.h>
#include "View.h"

#define PR_COOR(FUNC, x, y)                                 \
    do{                                                     \
        fout << FUNC << ": \t\t" << x << " " << y << std::endl; \
    }while(0)

static std::ofstream fout("logFile.txt");

class Tui:public View{

private:
    //int x_;
    //int y_;

    struct termios old_;
public:
    Tui();
    ~Tui();

    void    draw();
    void    getWinSize();
    void    drawLineY(int, int, int);
    void    drawLineX(int, int, int);
    void    gotoxy(int, int);//moves to the certain possition
    void    run();
    void    clearScreen();
    void    snakePainter(Coord, Dir);
    void    rabbitPainter(const Coord);

    //int     getX();
    //int     getY();
};

#endif