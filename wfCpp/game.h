#ifndef WFCPP_GAME_H
#define WFCPP_GAME_H

#include <list>
#include <utility>
#include <functional>

//auto

class Control;

enum Dir{
    UP      = 0,
    DOWN    = 1,
    RIGHT   = 2,
    LEFT    = 3,
    NO      = 4,
};

using Coord = std::pair<int, int>;

class Snake{
public:
    Snake();
    Snake(const Snake &);

    std::list<Coord>        body;
    Dir                     direction;
    Snake & operator=(Snake const &s);
};

using Rabbit = Coord;
using SnakePainter = std::function<void(Coord, Dir)>;//void is a return type

class Game{
public:
    Game();

    std::list<Snake*>      snakes;
    std::list<Rabbit>      rabbits;

    void paint(SnakePainter p);
    void add(Snake * p);
};

#endif