#ifndef WFCPP_GAME_H
#define WFCPP_GAME_H

#include <list>
#include <utility>
#include <functional>
#include <experimental/optional>
using namespace std::experimental;

class Control;

enum Dir{
    UP      = 0,
    DOWN    = 1,
    RIGHT   = 2,
    LEFT    = 3,
    NO      = 4,
};

//using Coord = std::pair<int, int>;

struct Coord:public std::pair<int, int>{
  using Base = std::pair<int, int>;
  int distance(const Coord&)const;
  using Base::Base;
};

class Snake{
public:
    Snake                               ();
    Snake                               (const Snake &);

    std::list<Coord>        body;
    Dir                     direction;
    Snake &                 operator=   (Snake const &s);
    void                    move        ();
    Coord                   next        ();
};

using Rabbit        = Coord;
using SnakePainter  = std::function<void(Coord, Dir)>;//void is a return type
using RabbitPainter = std::function<void(Coord)>;

class Control;

class Game{
public:
    Game();

    std::list<Snake*>      snakes;
    std::list<Rabbit>      rabbits;

    void    paint           (SnakePainter sp, RabbitPainter rb);
    void    add             (Snake * p);
    void    move            ();
    Coord   getFreeCoord    () const; //if the Coordinate is free or not
    bool    isFree          (const Coord c) const;
    char    checkForSnakes  (const Coord c) const;
    void    killRabbit      (const Coord c);

    void    createRabbit    ();
    optional<Coord>         near        (const Coord& c) const;

    //single-tone
    static Game *  game_inst_;
    static Game *  get();


    std::list<Control*>    controls;
};

#endif