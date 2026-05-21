#pragma once

#include "objects.hpp"
#include <iostream>
#include <windows.h>

namespace tar {
	class GameLevel {
		private:
			Mario mario;
			
			Brick* bricks = nullptr;
			std::size_t brick_length = 0;
			
			Moving* movings = nullptr;
			std::size_t moving_length = 0;
			
			int level_num = 1;
			int max_lvl = 3;
			int score = 0;

			void addBrick(const Brick& new_brick);
			void freeMemory();

		public:
			GameLevel() = default;
			~GameLevel();

			Mario& getMario() { return mario; }
			Brick* getBricks() { return bricks; }
			std::size_t getBrickLength() const { return brick_length; }
			
			Moving* getMovings() { return movings; }
			std::size_t getMovingLength() const { return moving_length; }
			
			int getScore() const { return score; }
			int getLevelNum() const { return level_num; }
			int getMaxLvl() const { return max_lvl; }
			
			void setLevelNum(int num) { level_num = num; }
			void addScore(int s) { score += s; }

			void createLevel();
			void marioCollision();
			void playerDead();
			void horizonMoveMap(float dx);
			
			void spawnMoving(float x, float y, char type, float v_speed);
			void deleteMoving(std::size_t index);
	};
}

