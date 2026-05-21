#include "level.hpp"

using namespace tar;

int main() {
    GameLevel level;
    char MAP[MAP_HEIGHT][MAP_WIDTH + 1] = {};
    
    level.createLevel();

    do {
        clear_map(MAP);
        Mario& player = level.getMario();

        if (!player.getIsFly() && GetKeyState(VK_SPACE) < 0)
            player.setVertSpeed(-1.0f);
        if (GetKeyState('A') < 0)
            level.horizonMoveMap(1.0f);
        if (GetKeyState('D') < 0)
            level.horizonMoveMap(-1.0f);

        if (player.getY() > MAP_HEIGHT)
            level.playerDead();

        player.vertMove(level, true);
        level.marioCollision();

        Brick* bricks = level.getBricks();
        std::size_t brick_count = level.getBrickLength();
        for (size_t i = 0; i < brick_count; ++i) {
            bricks[i].putOnMap(MAP);
        }

        Moving* movings = level.getMovings();
        for (size_t i = 0; i < level.getMovingLength(); ++i) {
            movings[i].vertMove(level, false);
            movings[i].horizonMove(level);
            movings[i].putOnMap(MAP);
            movings = level.getMovings(); 
        }

        player.putOnMap(MAP);
        put_score_on_map(level.getScore(), MAP);

        set_cur(0, 0);
        show_map(MAP);
        Sleep(10);
        
    } while (GetKeyState(VK_ESCAPE) >= 0);

    return 0;
}
