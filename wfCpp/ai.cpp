#include "ai.h"
#include <iostream>
#include <algorithm>
#include <random>

Ai::Ai(Snake * s, Game * g) :
    Control (s),
    game_   (g)
{}

Ai::~Ai() { std::cout << "Dstctr" << std::endl; }

void Ai::onMove()
{
    Dir dirs[] = {UP, DOWN, LEFT, RIGHT};

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(dirs, dirs + 4, g);

    auto nearest_rabbit_coord = game_->near(snake->body.front());

    auto cur_dist = nearest_rabbit_coord->distance(snake->body.front());
    for(int i = 0; i < 4; i++)
    {
        snake->direction = dirs[i];

        auto next_dist = nearest_rabbit_coord->distance(snake->next());
        if((cur_dist > next_dist)&&(game_->isFree(snake->next())))
        {
            break;
        }
    }
}