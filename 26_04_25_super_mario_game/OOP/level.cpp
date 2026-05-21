#include "level.hpp"
#include <algorithm>
#include <string>

using namespace tar;

GameLevel::~GameLevel() {
    freeMemory();
}

void GameLevel::freeMemory() {
    delete[] bricks;
    bricks = nullptr;
    brick_length = 0;
    
    delete[] movings;
    movings = nullptr;
    moving_length = 0;
}

void GameLevel::addBrick(const Brick& new_brick) {
    brick_length++;
    Brick* new_arr = new Brick[brick_length];
    if (bricks != nullptr) {
        std::copy(bricks, bricks + brick_length - 1, new_arr);
        delete[] bricks;
    }
    bricks = new_arr;
    bricks[brick_length - 1] = new_brick;
}

void GameLevel::spawnMoving(float x, float y, char type, float v_speed) {
    moving_length++;
    Moving* new_arr = new Moving[moving_length];
    if (movings != nullptr) {
        std::copy(movings, movings + moving_length - 1, new_arr);
        delete[] movings;
    }
    movings = new_arr;
    
    movings[moving_length - 1] = Moving(x, y, 3.0f, 2.0f, type);
    movings[moving_length - 1].setVertSpeed(v_speed);
}

void GameLevel::deleteMoving(std::size_t index) {
    if (index >= moving_length) return;
    
    movings[index] = movings[moving_length - 1];
    moving_length--;
    
    if (moving_length == 0) {
        delete[] movings;
        movings = nullptr;
        return;
    }
    
    Moving* new_arr = new Moving[moving_length];
    std::copy(movings, movings + moving_length, new_arr);
    delete[] movings;
    movings = new_arr;
}

void GameLevel::horizonMoveMap(float dx) {
    mario.changeX(-dx);
    for (size_t i = 0; i < brick_length; ++i) {
        if (mario.isCollision(bricks[i])) {
            mario.changeX(dx);
            return;
        }
    }
    mario.changeX(dx);
    
    for (size_t i = 0; i < brick_length; ++i) bricks[i].changeX(dx);
    for (size_t i = 0; i < moving_length; ++i) movings[i].changeX(dx);
}

void GameLevel::marioCollision() {
    for (size_t i = 0; i < moving_length; ++i) {
        if (mario.isCollision(movings[i])) {
            if (movings[i].getType() == 'o') {
                if (mario.getIsFly() && mario.getVertSpeed() > 0 && 
                    (mario.getY() + mario.getHeight() < movings[i].getY() + movings[i].getHeight() * 0.5f)) {
                    score += 50;
                    deleteMoving(i);
                    --i;
                    continue;
                } else {
                    playerDead();
                    return;
                }
            }
            if (movings[i].getType() == '$') {
                score += 100;
                deleteMoving(i);
                --i;
                continue;
            }
        }
    }
}

void GameLevel::playerDead() {
    std::system("color 4F");
    Sleep(500);
    createLevel();
}

void GameLevel::createLevel() {
    std::system("color 9F");
    freeMemory();
    mario.reset();
    score = 0;
    
    switch(level_num) {
        case 1:
            addBrick(Brick(20, 20, 40, 5, '#'));
            addBrick(Brick(60, 15, 40, 10, '#'));
            addBrick(Brick(100, 20, 20, 5, '#'));
            addBrick(Brick(120, 15, 10, 10, '#'));
            addBrick(Brick(150, 20, 40, 5, '#'));
            addBrick(Brick(210, 15, 10, 10, '+'));
            addBrick(Brick(30, 10, 5, 3, '?'));
            addBrick(Brick(50, 10, 5, 3, '?'));
            addBrick(Brick(60, 5, 10, 3, '-'));
            addBrick(Brick(70, 5, 5, 3, '?'));
            addBrick(Brick(75, 5, 5, 3, '-'));
            addBrick(Brick(80, 5, 5, 3, '?'));
            addBrick(Brick(85, 5, 10, 3, '-'));
            spawnMoving(25, 10, 'o', 0.0f);
            spawnMoving(80, 10, 'o', 0.0f);
            break;
        case 2:
            addBrick(Brick(20, 20, 40, 5, '#'));
            addBrick(Brick(60, 15, 10, 5, '#'));
            addBrick(Brick(80, 20, 20, 5, '#'));
            addBrick(Brick(120, 15, 10, 10, '#'));
            addBrick(Brick(150, 20, 40, 5, '#'));
            addBrick(Brick(210, 15, 10, 10, '+'));
            spawnMoving(25, 10, 'o', 0.0f);
            spawnMoving(80, 10, 'o', 0.0f);
            spawnMoving(65, 10, 'o', 0.0f);
            spawnMoving(120, 10, 'o', 0.0f);
            spawnMoving(160, 10, 'o', 0.0f);
            spawnMoving(175, 10, 'o', 0.0f);
            break;
        case 3:
            addBrick(Brick(20, 20, 40, 5, '#'));
            addBrick(Brick(80, 20, 15, 5, '#'));
            addBrick(Brick(120, 15, 15, 10, '#'));
            addBrick(Brick(160, 10, 15, 15, '+'));
            spawnMoving(25, 10, 'o', 0.0f);
            spawnMoving(50, 10, 'o', 0.0f);
            spawnMoving(80, 10, 'o', 0.0f);
            spawnMoving(90, 10, 'o', 0.0f);
            spawnMoving(120, 10, 'o', 0.0f);
            spawnMoving(130, 10, 'o', 0.0f);
            break;
    }
}

void clear_map(char (&MAP)[MAP_HEIGHT][MAP_WIDTH + 1]) {
    for (int i = 0; i < MAP_WIDTH; ++i) MAP[0][i] = ' ';
    MAP[0][MAP_WIDTH] = '\0';
    for (int j = 1; j < MAP_HEIGHT; ++j) std::copy(MAP[0], MAP[0] + MAP_WIDTH + 1, MAP[j]);
}

void put_score_on_map(int score, char (&MAP)[MAP_HEIGHT][MAP_WIDTH + 1]) {
    std::string score_str = "SCORE: " + std::to_string(score);
    for (size_t i = 0; i < score_str.length() && (i + 5) < MAP_WIDTH; ++i)
        MAP[1][i + 5] = score_str[i];
}

bool is_pos_in_map(int x, int y) {
    return (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT);
}

void set_cur(int x, int y) {
    COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void show_map(char (&MAP)[MAP_HEIGHT][MAP_WIDTH + 1]) {
    MAP[MAP_HEIGHT - 1][MAP_WIDTH - 1] = '\0';
    for (int j = 0; j < MAP_HEIGHT; ++j) std::cout << MAP[j];
}
