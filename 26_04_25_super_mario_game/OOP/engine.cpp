#include <algorithm>
#include <string>
#include <iostream>
#include <windows.h>

#include "engine.hpp"


void tar::handle_input(GameLevel& level)
{
    Mario& mario = level.getMario();
	
	if (!mario.getIsFly() && GetKeyState(VK_SPACE) < 0)
        mario.setVertSpeed(-1.0f);
    if (GetKeyState('A') < 0)
        level.horizonMoveMap(1.0f);
    if (GetKeyState('D') < 0)
        level.horizonMoveMap(-1.0f);
}

void tar::update(GameLevel& level)
{
    Mario& mario = level.getMario();
	
	Moving* movings = level.getMovings();
	std::size_t moving_length = level.getMovingLength();
	
	if (mario.getY() > MAP_HEIGHT) {
        level.playerDead();
        return; 
    }

    mario.vertMove(level, true);
    level.marioCollision();

    for (size_t i = 0; i < moving_length; ++i) {
        movings[i].vertMove(level, false);
        movings[i].horizonMove(level);
    }
}

void tar::render(char (&map)[MAP_HEIGHT][MAP_WIDTH + 1],
				 GameLevel& level)
{
    tar::clear_map(map);
	
	Mario& mario = level.getMario();
	
	Brick* bricks = level.getBricks();
	std::size_t brick_length = level.getBrickLength();
	
	Moving* movings = level.getMovings();
	std::size_t moving_length = level.getMovingLength();
	
	int score = level.getScore();

    for (size_t i = 0; i < brick_length; ++i) {
        bricks[i].putOnMap(map);
    }

    for (size_t i = 0; i < moving_length; ++i) {
        movings[i].putOnMap(map);
    }

    mario.putOnMap(map);
    tar::put_score_on_map(score, map);

    tar::set_cur(0, 0);
    tar::show_map(map);
}