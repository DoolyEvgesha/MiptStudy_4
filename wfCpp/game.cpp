#include <iostream>
#include <climits>
#include "game.h"
#include "View.h"
#include "control.h"
#include <random>

int Coord::distance(const Coord & c) const {return (c.first + c.second);}

optional<Coord> Game::near(const Coord &c) const
{
    int min = INT_MAX;
    optional<Coord> closest_rabbit;//no value

    for(auto i : rabbits)
    {
        if(i.distance(c) < min)
        {
            min = i.distance(c);
            closest_rabbit = i;// if there is somwthing, we take it
        }
    }
    return closest_rabbit;
}

Game::Game()
{
    View * v = View::get();
    v->setOnTimer(500, std::bind(&Game::move, this));

    for(int i = 0; i < 5; ++i)
    {
        createRabbit();
        View::get()->timer_.pop_back();
    }

    v->setOnTimer(500, std::bind(&Game::move, this));
    v->setOnTimer(5,   std::bind(&Game::move, this));
}

Snake::Snake()
{
    direction   = RIGHT;
    Coord start = Game::get()->getFreeCoord();
    for(int i = 0; i < 4; i++)
        body.emplace_back(Coord(start.first, start.second));
    //TODO:check why Idea told to replace push_back with emplace_back
        //body.push_back(Coord(start.first, start.second));
}

Snake::Snake(const Snake & s):
    direction   (s.direction),
    body        (s.body)
{}

Game * Game::game_inst_;

Game * Game::get()
{
    if(game_inst_ != nullptr)
        return Game::game_inst_;
    Game::game_inst_ = new Game;
    return Game::game_inst_;
}

Coord Game::getFreeCoord() const
{
    Coord res;

    while(1)
    {
        res.first   = rand() % View::get()->view_x_;
        res.second  = rand() % View::get()->view_y_;

        if(res.first    == 0 || res.first   == 1)   res.first  += 5;
        if(res.second   == 0 || res.second  == 1)   res.second += 5;

        if(res.first  == View::get()->view_x_ - 1)     res.first  -= 5;
        if(res.second == View::get()->view_y_ - 1)     res.second -= 5;

        if(isFree(res)) {
            return res;
        }
    }
}
bool Game::isFree(const Coord c) const
{
    //check that snake doesn't eat itself
    for(const auto i : snakes)
        for(const auto &b : i->body)
            if(c == b)
                return false;

    //check there is no rabbit
    for(const Coord &i : rabbits)
        if(i == c)
            return false;

    if(c.first  <= 1)   return false;
    if(c.second <= 1)   return false;

    if(c.first  >= View::get()->view_x_ - 1)   return false;
    if(c.second >= View::get()->view_y_ - 1)   return false;

    return true;
}

void Game::paint(SnakePainter snake_pointer, RabbitPainter rabbit_painter)
{
    bool f = true;
    for(const auto s: snakes)
    {
        for(const auto & c:s->body)
        {
            snake_pointer(c, f ? s->direction: NO);
            f = false;
        }
    }

    for(const auto & r: rabbits) {
        rabbit_painter(r);
    }
}

void Game::add(Snake * p)
{
    snakes.push_back(p);
}

Snake& Snake::operator=(Snake const &s)
{
    body = s.body;
    direction = s.direction;
    return *this;
}

void Game::move()
{
    for(auto c:controls)
    {
        c->onMove();
    }
    for(auto s:snakes)
    {
        s->move();
    }
}

Coord Snake::next()
{
    auto a = body.front();

    switch(direction){
        case UP:
            a.first--;
            break;
        case DOWN:
            a.first++;
            break;
        case RIGHT:
            a.second++;
            break;
        case LEFT:
            a.second--;
            break;
    }
    return a;
}

void Snake::move(){

    auto a = next();

    switch(Game::get()->checkForSnakes(a))
    {
        case ' ':
            body.push_front(a);
            body.pop_back();
            break;

        case 's':
            //TODO:snake dies
            break;

        case 'b':
            //TODO:snake dies as well
            break;

        case 'r':
            Game::get()->killRabbit(a);
            body.push_front(a);
            break;

        default:
            break;
    }

    body.push_front(a);
    body.pop_back();
}

void Game::killRabbit(const Coord c)
{
    for(const auto &r : rabbits)
        if(c == r)
        {
            rabbits.remove(r);
            break;
        }
}

char Game::checkForSnakes(const Coord c) const
{

    for(const auto i : snakes)
        for(const auto & b : i->body)
            if(c == b)
                return 's';

    for(const auto & r : rabbits)
        if(c == r)
            return 'r';

    //check for bounds
    if(c.first == 1 || c.second == 1 || c.second == View::get()->view_x_ || c.second == View::get()->view_y_)
        return 'b';

    return ' ';
}

void Game::createRabbit()
{
    Coord res;
    srand(1);
    //TODO: check what time you need
    View::get()->setOnTimer(8, std::bind(&Game::createRabbit, this));

    while(1) {

        res.first =   rand() % View::get()->view_x_;
        res.second =  rand() % View::get()->view_y_;

        if(res.first  == 0)    res.first ++;
        if(res.second == 0)    res.second ++;

        if(res.first  == View::get()->view_x_ - 1)     res.first --;
        if(res.second == View::get()->view_y_ - 1)     res.second --;

        if(isFree(res)) {
            rabbits.push_back(res);
            return;
        }
    }
}