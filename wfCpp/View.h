#ifndef VIEW_H
#define VIEW_H

#include "game.h"
#include "keypressable.h"

using Timeoutable = std::function<void ()>;

class View {
public:
    void virtual        draw        ()                  = 0;
    void virtual        run         ()                  = 0;

    virtual             ~View       ()                  = 0;

    static View *       inst_;
    //static View *       get         (const char * type = nullptr);
    static View *       get         ();
    virtual void        getWinSize  ()                  = 0;

    void                setOnKey    (KeyPressable * key) { onkey_delegate_ = key; };
    KeyPressable *      onkey_delegate_;

    Game *              game_;
    void                setModel    (Game * g) { game_ = g; };

    void virtual        snakePainter(Coord c, Dir d)    = 0;

    void                setOnTimer  (int time, Timeoutable timer)
    { timer_.first = time; timer_.second = timer; };

    std::pair<int, Timeoutable> timer_;
//private:

};

#endif
