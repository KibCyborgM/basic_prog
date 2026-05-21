#include "engine.hpp"
#include "level.hpp"

using namespace tar;

int main() {
    GameLevel level;
    char map[MAP_HEIGHT][MAP_WIDTH + 1] = {};
    
    level.createLevel();

    do {
        handle_input(level);
        update(level);
        render(map, level);
        
        Sleep(10);
        
    } while (GetKeyState(VK_ESCAPE) >= 0);

    return 0;
}
