#include "game.h"

Game::Game()
{
    //snakes.push_back(Snake());
}

Snake::Snake()
{
    direction = UP;
    body.push_back(Coord(10, 11));
    body.push_back(Coord(11, 11));
    body.push_back(Coord(12, 11));
}

Snake::Snake(const Snake & s):
    direction   (s.direction),
    body        (s.body)
{}

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
}

void Game::move()
{
    for(auto s:snakes)
        s->move();
}

void Snake::move(){
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

    body.push_front(a);
    body.pop_back();
}