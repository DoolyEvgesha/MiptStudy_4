#include "game.h"

Game::Game()
{
    snakes.push_back(Snake());
}

Snake::Snake()
{
    direction = UP;
    body.push_back(Coord(10, 11));
    body.push_back(Coord(11, 11));
    body.push_back(Coord(12, 11));
}

void Game::paint(SnakePainter pointer)
{
    bool f = true;
    for(const auto & s: snakes)
    {
        for(const auto & c:s.body)
        {
            pointer(c, f ? s.direction: NO);
            f = false;
        }
    }
}

