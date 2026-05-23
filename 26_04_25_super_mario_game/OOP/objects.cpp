#include <cmath>
#include <cstdlib>
#include <windows.h>

#include "objects.hpp"
#include "level.hpp"

using namespace tar;

Object::Object(float x_pos, float y_pos, float w, float h, char type)
    : x(x_pos), y(y_pos), width(w), height(h), c_type(type) {}

bool Object::isCollision(const Object& other) const {
    return (((x + width) > other.getX())
            && (x < (other.getX() + other.getWidth()))
            && ((y + height) > other.getY())
            && (y < (other.getY() + other.getHeight())));
}

void Object::putOnMap(char (&map)[MAP_HEIGHT][MAP_WIDTH + 1]) const {
    int ix = static_cast<int>(std::round(x));
    int iy = static_cast<int>(std::round(y));
    int i_width = static_cast<int>(std::round(width));
    int i_height = static_cast<int>(std::round(height));
    
    for (int i = ix; i < (ix + i_width); ++i) {
        for (int j = iy; j < (iy + i_height); ++j)
            if (is_pos_in_map(i, j))
                map[j][i] = c_type;
    }
}

void Mario::reset() {
	setPos(39.0f, 10.0f);
	setVertSpeed(0.0f);
	setIsFly(false); 
}

void Moving::horizonMove(GameLevel& level)
{
    changeX(getHorizSpeed());
    
    Brick* bricks = level.getBricks();
    std::size_t brick_len = level.getBrickLength();
    
    for (size_t i = 0; i < brick_len; ++i) {
        if (isCollision(bricks[i])) {
            changeX(-getHorizSpeed());
            setHorizSpeed(-getHorizSpeed());
            return;
        }
    }
    
    if (getType() == 'o') {
        Moving tmp = *this;
        tmp.vertMove(level, false);
        if (tmp.getIsFly()) {
            changeX(-getHorizSpeed());
            setHorizSpeed(-getHorizSpeed());
        }
    }
}

void Moving::vertMove(GameLevel& level, bool is_mario) {
	setIsFly(true);
    setVertSpeed(getVertSpeed() + 0.05f);
    changeY(getVertSpeed());
    
    Brick* bricks = level.getBricks();
    std::size_t brick_len = level.getBrickLength();
    
    for (size_t i = 0; i < brick_len; ++i) {
        if (isCollision(bricks[i])) {
            if (vert_speed > 0)
                is_fly = false;
            
            if (bricks[i].getType() == '?' && vert_speed < 0 && is_mario) {
                bricks[i].setType('-');
                level.spawnMoving(bricks[i].getX(), bricks[i].getY() - 3.0f, '$', -0.7f);
            }
            
            changeY(-getVertSpeed());
            setVertSpeed(0.0f);
            
            if (bricks[i].getType() == '+') {
                int next_lvl = level.getLevelNum() + 1;
                if (next_lvl > level.getMaxLvl())
                    next_lvl = 1;
                level.setLevelNum(next_lvl);
                std::system("color 2F");
                Sleep(500);
                level.createLevel();
            }
            break;
        }
    }
}
