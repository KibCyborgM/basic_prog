#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <windows.h>
#include <cstdlib>

constexpr int MAP_HEIGHT = 25;
constexpr int MAP_WIDTH  = 80;

struct S_OBJECT {
    float x = 0.0f, y = 0.0f;
    float width = 0.0f, height = 0.0f;
    float vert_speed = 0.0f;
    bool is_fly = false;
    char c_type = ' ';
    float horiz_speed = 0.2f;
};

char MAP[MAP_HEIGHT][MAP_WIDTH + 1] = {};
S_OBJECT MARIO;
S_OBJECT* BRICK = nullptr;
int BRICK_LENGTH = 0;
S_OBJECT* moving = nullptr;
int moving_length = 0;
int LEVEL = 1;
int SCORE = 0;


void clear_map();
void create_level(int lvl);
void delete_moving(int i);
S_OBJECT* get_new_brick();
S_OBJECT* get_new_moving();
void horizon_move_map(float dx);
void horizon_move_object(S_OBJECT* obj, int& MAX_LVL);
void init_object(S_OBJECT* obj, float x_pos, float y_pos, float o_width, float o_height, char in_type);
bool is_collision(S_OBJECT o1, S_OBJECT o2);
bool is_pos_in_map(int x, int y);
void mario_collision(int& MAX_LVL);
void player_dead();
void put_object_on_map(S_OBJECT obj);
void put_score_on_map();
void set_cur(int x, int y);
void set_object_pos(S_OBJECT* obj, float x_pos, float y_pos);
void show_map();
void vert_move_object(S_OBJECT* obj, int& MAX_LVL);

int main() {
	int MAX_LVL = 0;
	
    create_level(LEVEL);

    do {
        clear_map();
        if (!MARIO.is_fly && GetKeyState(VK_SPACE) < 0)
            MARIO.vert_speed = -1.0f;
        if (GetKeyState('A') < 0)
            horizon_move_map(1.0f);
        if (GetKeyState('D') < 0)
            horizon_move_map(-1.0f);

        if (MARIO.y > MAP_HEIGHT)
            player_dead();

        vert_move_object(&MARIO, MAX_LVL);
        mario_collision(MAX_LVL);

        for (int i = 0; i < BRICK_LENGTH; ++i)
            put_object_on_map(BRICK[i]);

        for (int i = 0; i < moving_length; ++i) {
            vert_move_object(moving + i, MAX_LVL);
            horizon_move_object(moving + i, MAX_LVL);
            put_object_on_map(moving[i]);
        }

        put_object_on_map(MARIO);
        put_score_on_map();

        set_cur(0, 0);
        show_map();
        Sleep(10);
    } while (GetKeyState(VK_ESCAPE) >= 0);
    return 0;
}


void clear_map() {
    for (int i = 0; i < MAP_WIDTH; ++i)
        MAP[0][i] = ' ';
    
    MAP[0][MAP_WIDTH] = '\0';
    
    for (int j = 1; j < MAP_HEIGHT; ++j)
        std::copy(MAP[0], MAP[0] + MAP_WIDTH + 1, MAP[j]);
}

void create_level(int lvl) {
    std::system("color 9F");
    
    BRICK_LENGTH = 0;
    delete[] BRICK;
    BRICK = nullptr;
    
    moving_length = 0;
    delete[] moving;
    moving = nullptr;
    
    init_object(&MARIO, 39.0f, 10.0f, 3.0f, 3.0f, '@');
    SCORE = 0;
    
    if (lvl == 1) {
        init_object(get_new_brick(), 20, 20, 40, 5, '#');
        init_object(get_new_brick(), 60, 15, 40, 10, '#');
        init_object(get_new_brick(), 100, 20, 20, 5, '#');
        init_object(get_new_brick(), 120, 15, 10, 10, '#');
        init_object(get_new_brick(), 150, 20, 40, 5, '#');
        init_object(get_new_brick(), 210, 15, 10, 10, '+');
        init_object(get_new_brick(), 30, 10, 5, 3, '?');
        init_object(get_new_brick(), 50, 10, 5, 3, '?');
        init_object(get_new_brick(), 60, 5, 10, 3, '-');
        init_object(get_new_brick(), 70, 5, 5, 3, '?');
        init_object(get_new_brick(), 75, 5, 5, 3, '-');
        init_object(get_new_brick(), 80, 5, 5, 3, '?');
        init_object(get_new_brick(), 85, 5, 10, 3, '-');
        init_object(get_new_moving(), 25, 10, 3, 2, 'o');
        init_object(get_new_moving(), 80, 10, 3, 2, 'o');
    }
    if (lvl == 2) {
        init_object(get_new_brick(), 20, 20, 40, 5, '#');
        init_object(get_new_brick(), 60, 15, 10, 5, '#');
        init_object(get_new_brick(), 80, 20, 20, 5, '#');
        init_object(get_new_brick(), 120, 15, 10, 10, '#');
        init_object(get_new_brick(), 150, 20, 40, 5, '#');
        init_object(get_new_brick(), 210, 15, 10, 10, '+');
        init_object(get_new_moving(), 25, 10, 3, 2, 'o');
        init_object(get_new_moving(), 80, 10, 3, 2, 'o');
        init_object(get_new_moving(), 65, 10, 3, 2, 'o');
        init_object(get_new_moving(), 120, 10, 3, 2, 'o');
        init_object(get_new_moving(), 160, 10, 3, 2, 'o');
        init_object(get_new_moving(), 175, 10, 3, 2, 'o');
    }
    if (lvl == 3) {
        init_object(get_new_brick(), 20, 20, 40, 5, '#');
        init_object(get_new_brick(), 80, 20, 15, 5, '#');
        init_object(get_new_brick(), 120, 15, 15, 10, '#');
        init_object(get_new_brick(), 160, 10, 15, 15, '+');
        init_object(get_new_moving(), 25, 10, 3, 2, 'o');
        init_object(get_new_moving(), 50, 10, 3, 2, 'o');
        init_object(get_new_moving(), 80, 10, 3, 2, 'o');
        init_object(get_new_moving(), 90, 10, 3, 2, 'o');
        init_object(get_new_moving(), 120, 10, 3, 2, 'o');
        init_object(get_new_moving(), 130, 10, 3, 2, 'o');
    }
}

void delete_moving(int i) {
    if (i < 0 || i >= moving_length)
        return;
    
    moving[i] = moving[moving_length - 1];
    moving_length--;   
}

S_OBJECT* get_new_brick() {
    BRICK_LENGTH++;
    S_OBJECT* new_arr = new S_OBJECT[BRICK_LENGTH];
    if (BRICK != nullptr) {
        std::copy(BRICK, BRICK + BRICK_LENGTH - 1, new_arr);
        delete[] BRICK;
    }
    BRICK = new_arr;
    return BRICK + BRICK_LENGTH - 1;
}

S_OBJECT* get_new_moving() {
    moving_length++;
    S_OBJECT* new_arr = new S_OBJECT[moving_length];
    if (moving != nullptr) {
        std::copy(moving, moving + moving_length - 1, new_arr);
        delete[] moving;
    }
    moving = new_arr;
    return moving + moving_length - 1;
}

void horizon_move_map(float dx) {
    MARIO.x -= dx;
    for (int i = 0; i < BRICK_LENGTH; ++i)
        if (is_collision(MARIO, BRICK[i])) {
            MARIO.x += dx;
            return;
        }
    MARIO.x += dx;
    
    for (int i = 0; i < BRICK_LENGTH; ++i)
        BRICK[i].x += dx;
    for (int i = 0; i < moving_length; ++i)
        moving[i].x += dx;
}

void horizon_move_object(S_OBJECT* obj, int& MAX_LVL) {
    obj->x += obj->horiz_speed;
    
    for (int i = 0; i < BRICK_LENGTH; ++i)
        if (is_collision(*obj, BRICK[i])) {
            obj->x -= obj->horiz_speed;
            obj->horiz_speed = -obj->horiz_speed;
            return;
        }
    
    if (obj->c_type == 'o') {
        S_OBJECT tmp = *obj;
        vert_move_object(&tmp, MAX_LVL);
        if (tmp.is_fly == true) {
            obj->x -= obj->horiz_speed;
            obj->horiz_speed = -obj->horiz_speed;
        }
    }
}

void init_object(S_OBJECT* obj, float x_pos, float y_pos,
                 float o_width, float o_height, char in_type) {
    set_object_pos(obj, x_pos, y_pos);
    obj->width = o_width;
    obj->height = o_height;
    obj->vert_speed = 0.0f;
    obj->c_type = in_type;
    obj->horiz_speed = 0.2f;
}

bool is_collision(S_OBJECT o1, S_OBJECT o2) {
    return (((o1.x + o1.width) > o2.x)
            && (o1.x < (o2.x + o2.width))
            && ((o1.y + o1.height) > o2.y)
            && (o1.y < (o2.y + o2.height)));
}

bool is_pos_in_map(int x, int y) {
    return ((x >= 0)
            && (x < MAP_WIDTH)
            && (y >= 0)
            && (y < MAP_HEIGHT));
}

void mario_collision(int& MAX_LVL) {
    for (int i = 0; i < moving_length; ++i)
        if (is_collision(MARIO, moving[i])) {
            if (moving[i].c_type == 'o') {
                if ((MARIO.is_fly == true) 
                    && (MARIO.vert_speed > 0) 
                    && (MARIO.y + MARIO.height < moving[i].y + moving[i].height * 0.5f)) {
                    
                    SCORE += 50;
                    delete_moving(i);
                    --i;
                    continue;
                }
                else
                    player_dead();
            }
            
            if (moving[i].c_type == '$') {
                SCORE += 100;
                delete_moving(i);
                --i;
                continue;
            }
        }
    MAX_LVL = 3;
}

void player_dead() {
    std::system("color 4F");
    Sleep(500);
    create_level(LEVEL);
}

void put_object_on_map(S_OBJECT obj) {
    int ix = static_cast<int>(std::round(obj.x));
    int iy = static_cast<int>(std::round(obj.y));
    int i_width = static_cast<int>(std::round(obj.width));
    int i_height = static_cast<int>(std::round(obj.height));
    
    for (int i = ix; i < (ix + i_width); ++i) {
        for (int j = iy; j < (iy + i_height); ++j)
            if (is_pos_in_map(i, j))
                MAP[j][i] = obj.c_type;
    }
}

void put_score_on_map() {
    std::string score_str = "SCORE: " + std::to_string(SCORE);
    for (size_t i = 0; i < score_str.length() && (i + 5) < MAP_WIDTH; ++i)
        MAP[1][i + 5] = score_str[i];
}

void set_cur(int x, int y) {
    COORD coord;
    coord.X = static_cast<SHORT>(x);
    coord.Y = static_cast<SHORT>(y);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void set_object_pos(S_OBJECT* obj, float x_pos, float y_pos) {
    obj->x = x_pos;
    obj->y = y_pos;
}

void show_map() {
    MAP[MAP_HEIGHT - 1][MAP_WIDTH - 1] = '\0';
    for (int j = 0; j < MAP_HEIGHT; ++j)
        std::cout << MAP[j];
}

void vert_move_object(S_OBJECT* obj, int& MAX_LVL) {
    obj->is_fly = true;
    obj->vert_speed += 0.05f;
    set_object_pos(obj, obj->x, obj->y + obj->vert_speed);
    
    for (int i = 0; i < BRICK_LENGTH; ++i)
        if (is_collision(*obj, BRICK[i])) {
            if (obj->vert_speed > 0)
                obj->is_fly = false;
            
            if ((BRICK[i].c_type == '?')
                && (obj->vert_speed < 0)
                && (obj == &MARIO)) {
                    
                BRICK[i].c_type = '-';
                init_object(get_new_moving(), BRICK[i].x, BRICK[i].y - 3.0f, 3.0f, 2.0f, '$');
                moving[moving_length - 1].vert_speed = -0.7f;
            }
            
            obj->y -= obj->vert_speed;
            obj->vert_speed = 0.0f;
            if (BRICK[i].c_type == '+') {
                ++LEVEL;
                if (LEVEL > MAX_LVL)
                    LEVEL = 1;
                std::system("color 2F");
                Sleep(500);
                create_level(LEVEL);
            }
            break;
        }
}