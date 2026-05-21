#pragma once

#include "level.hpp"
#include "objects.hpp"

namespace tar
{
	void handle_input(GameLevel& level);
	void update(GameLevel& level);
	void render(char (&map)[MAP_HEIGHT][MAP_WIDTH + 1],
				GameLevel& level);
}

