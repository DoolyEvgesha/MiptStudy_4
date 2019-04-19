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
    //v->destroy();
}

Snake::Snake()
{
    direction   = LEFT;
    int start   = rand() % 20;
    int y       = rand() % 20;
    for(int i = start; i < start + 10; i++)
        body.push_back(Coord(10 + i, y));
}

Snake::Snake(const Snake & s):
    direction   (s.direction),
    body        (s.body)
{}

bool Game::isFree(const Coord &c) const
{
    for(auto i : snakes)
    {
        for(Coord b : i->body)
        {
            if(c == b)
                return false;
        }
    }
    for(auto i : rabbits)
    {
        if(i == c)
            return false;
    }
    return true;
}

void Game::paint(SnakePainter pointer)
{
    bool f = true;
    for(const auto s: snakes)
    {
        for(const auto & c:s->body)
        {
            pointer(c, f ? s->direction: NO);
            f = false;
        }
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
    body.push_front(a);
    body.pop_back();
}