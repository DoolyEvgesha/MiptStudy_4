#include <iostream>
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <fstream>
#include <termios.h>
#include <unistd.h>
#include <functional>
#include <poll.h>

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

    drawLineX(0, x_, 0);
    drawLineY(0, y_, 0);
    drawLineX(0, x_, y_);
    drawLineY(0, y_, x_);

    game_->paint(std::bind(&View::snakePainter, this, _1, _2));
    fflush(stdout);

}

void Tui::getWinSize()
{
    struct winsize ws;
    ioctl(1, TIOCGWINSZ, &ws);

    x_ = ws.ws_row;
    y_ = ws.ws_col;
}

void onwinch(int x)
{
    View * v = View::get();

    v->draw();
}

Tui::Tui():
    x_(0),
    y_(0)
{
    setbuf(stdout, NULL);

    struct sigaction sa = {0};
    sa.sa_handler = onwinch;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGWINCH, &sa, 0);

    struct termios cur_mode;
    tcgetattr(STDIN_FILENO, &cur_mode);
    old_ = cur_mode;
    cfmakeraw(&cur_mode);
    tcsetattr(STDIN_FILENO, TCSANOW, &cur_mode);
}


void Tui::clearScreen()
{
    printf("\e[H\e[J");
}

Tui::~Tui()
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &old_);

    clearScreen();
    printf("Goodbye\n");
}

void Tui::run()
{/*
    while(1){
        int c;
        gotoxy(x_/2, y_/2);
        c = getchar();

        if(c == 'q')
            break;

        if(c != -1)
        {
            if(onkey_delegate_ != nullptr)
                onkey_delegate_->onkey(c);
        }
    }*/
    char cmd;
    nfds_t nfds = 1;
    int fds_ready = -1;

    pollfd * poll_stdin_master = new struct pollfd[nfds];
    pollfd * poll_stdin_set = new struct pollfd[nfds];

    poll_stdin_master[0].fd = STDIN_FILENO;
    poll_stdin_master[0].events = POLLIN;

    while(1)
    {
        draw();
        for(unsigned int i = 0; i < nfds; ++i)
            poll_stdin_set[i] = poll_stdin_master[i];

        fds_ready = poll(poll_stdin_set, nfds, timer_.first);
        if(fds_ready < 0) {
            fout << "ERROR: poll" << __PRETTY_FUNCTION__ << std::endl;
            break;
        }

        else if(fds_ready == 0) {
            timer_.second();
            continue;
        }

        for(unsigned int i = 0; i < nfds; ++i)
        {
            if(poll_stdin_set[i].revents == POLLIN)
            {
                if(read(poll_stdin_set[i].fd, &cmd, 1) == -1)
                {
                    fout << "ERROR: reading from pool set" << __PRETTY_FUNCTION__ << std::endl;
                    break;
                }

                if(onkey_delegate_) onkey_delegate_->onkey(cmd);
            }
        }

    }

    delete [] poll_stdin_master;
    delete [] poll_stdin_set;
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