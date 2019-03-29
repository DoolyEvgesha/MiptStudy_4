#ifndef VIEW_H
#define VIEW_H

#include "keypressable.h"
#include "game.h"

class View {
public:
    void virtual        draw        ()                  = 0;
    void virtual        run         ()                  = 0;

    virtual             ~View       ()                  = 0;

    static View *       inst;
    static View *       get         ();
    virtual void        getWinSize  ()                  = 0;

    void                setOnKey    (KeyPressable *);
    KeyPressable *      onkey_delegate;

    Game *              game;
    void                setModel    (Game *);

    void virtual        snakePainter(Coord c, Dir d)    = 0;
};

#endif
