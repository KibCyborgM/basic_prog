#include <algorithm>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <string>

#include <windows.h>


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

void clear_map(char (&MAP)[MAP_HEIGHT][MAP_WIDTH + 1]);

void create_level(S_OBJECT* MARIO, S_OBJECT*& BRICK, std::size_t& BRICK_LENGTH,
				  S_OBJECT*& moving, std::size_t& moving_length, 
				  int lvl, int& SCORE);
				  
void delete_moving(S_OBJECT*& moving, std::size_t& moving_length, int i);

S_OBJECT* get_new_brick(S_OBJECT*& BRICK, std::size_t& BRICK_LENGTH);

S_OBJECT* get_new_moving(S_OBJECT*& moving, std::size_t& moving_length);

void horizon_move_map(S_OBJECT* MARIO, S_OBJECT*& BRICK, std::size_t& BRICK_LENGTH, 
					  S_OBJECT*& moving, std::size_t& moving_length, float dx);
					  
void horizon_move_object(S_OBJECT* obj, S_OBJECT* MARIO, 
						 S_OBJECT*& BRICK, std::size_t& BRICK_LENGTH, 
						 S_OBJECT*& moving, std::size_t& moving_length, 
						 int& LEVEL, int& MAX_LVL, int& SCORE);
						 
void init_object(S_OBJECT* obj, float x_pos, float y_pos, 
				 float o_width, float o_height, char in_type);
				 
bool is_collision(S_OBJECT o1, S_OBJECT o2);

bool is_pos_in_map(int x, int y);

void mario_collision(S_OBJECT* MARIO, S_OBJECT*& BRICK, std::size_t& BRICK_LENGTH,
					 S_OBJECT*& moving, std::size_t& moving_length,
					 int& LEVEL, int& MAX_LVL, int& SCORE);
					 
void player_dead(S_OBJECT* MARIO, S_OBJECT*& BRICK, std::size_t& BRICK_LENGTH,
				 S_OBJECT*& moving, std::size_t& moving_length,
				 int& LEVEL, int& SCORE);
				 
void put_object_on_map(S_OBJECT obj, char (&MAP)[MAP_HEIGHT][MAP_WIDTH + 1]);

void put_score_on_map(int& SCORE, char (&MAP)[MAP_HEIGHT][MAP_WIDTH + 1]);

void set_cur(int x, int y);

void set_object_pos(S_OBJECT* obj, float x_pos, float y_pos);

void show_map(char (&MAP)[MAP_HEIGHT][MAP_WIDTH + 1]);

void vert_move_object(S_OBJECT* obj, S_OBJECT* MARIO,
					  S_OBJECT*& BRICK, std::size_t& BRICK_LENGTH,
					  S_OBJECT*& moving, std::size_t& moving_length,
					  int& LEVEL, int& MAX_LVL, int& SCORE);

int main()
{
	S_OBJECT MARIO;
	S_OBJECT* BRICK = nullptr;
	std::size_t BRICK_LENGTH = 0;
	S_OBJECT* moving = nullptr;
	std::size_t moving_length = 0;
	
	char MAP[MAP_HEIGHT][MAP_WIDTH + 1] = {};
	int LEVEL = 1;
	int MAX_LVL = 0;
	int SCORE = 0;
	
    create_level(&MARIO, BRICK, BRICK_LENGTH, moving, moving_length, LEVEL, SCORE);

    do {
        clear_map(MAP);
        if (!MARIO.is_fly && GetKeyState(VK_SPACE) < 0)
            MARIO.vert_speed = -1.0f;
        if (GetKeyState('A') < 0)
            horizon_move_map(&MARIO, BRICK, BRICK_LENGTH, moving, moving_length, 1.0f);
        if (GetKeyState('D') < 0)
            horizon_move_map(&MARIO, BRICK, BRICK_LENGTH, moving, moving_length, -1.0f);

        if (MARIO.y > MAP_HEIGHT)
            player_dead(&MARIO, BRICK, BRICK_LENGTH, moving, moving_length, LEVEL, SCORE);

        vert_move_object(&MARIO, &MARIO, BRICK, BRICK_LENGTH, moving, moving_length, LEVEL, MAX_LVL, SCORE);
        mario_collision(&MARIO, BRICK, BRICK_LENGTH, moving, moving_length, LEVEL, MAX_LVL, SCORE);

        for (int i = 0; i < BRICK_LENGTH; ++i)
            put_object_on_map(BRICK[i], MAP);

        for (int i = 0; i < moving_length; ++i) {
            vert_move_object(moving + i, &MARIO, BRICK, BRICK_LENGTH, moving, moving_length, LEVEL, MAX_LVL, SCORE);
            horizon_move_object(moving + i, &MARIO, BRICK, BRICK_LENGTH, moving, moving_length, LEVEL, MAX_LVL, SCORE);
            put_object_on_map(moving[i], MAP);
        }

        put_object_on_map(MARIO, MAP);
        put_score_on_map(SCORE, MAP);

        set_cur(0, 0);
        show_map(MAP);
        Sleep(10);
    } while (GetKeyState(VK_ESCAPE) >= 0);
    return 0;
}


void clear_map(char (&MAP)[MAP_HEIGHT][MAP_WIDTH + 1])
{
    for (int i = 0; i < MAP_WIDTH; ++i)
        MAP[0][i] = ' ';
    
    MAP[0][MAP_WIDTH] = '\0';
    
    for (int j = 1; j < MAP_HEIGHT; ++j)
        std::copy(MAP[0], MAP[0] + MAP_WIDTH + 1, MAP[j]);
}

void create_level(S_OBJECT* MARIO, S_OBJECT*& BRICK, std::size_t& BRICK_LENGTH,
				  S_OBJECT*& moving, std::size_t& moving_length, 
				  int lvl, int& SCORE)
{
    std::system("color 9F");
    
    BRICK_LENGTH = 0;
    delete[] BRICK;
    BRICK = nullptr;
    
    moving_length = 0;
    delete[] moving;
    moving = nullptr;
    
    init_object(MARIO, 39.0f, 10.0f, 3.0f, 3.0f, '@');
    SCORE = 0;
	
	switch(lvl){
    
		case 1:
			init_object(get_new_brick(BRICK, BRICK_LENGTH), 20, 20, 40, 5, '#');
			init_object(get_new_brick(BRICK, BRICK_LENGTH), 60, 15, 40, 10, '#');
			init_object(get_new_brick(BRICK, BRICK_LENGTH), 100, 20, 20, 5, '#');
			init_object(get_new_brick(BRICK, BRICK_LENGTH), 120, 15, 10, 10, '#');
			init_object(get_new_brick(BRICK, BRICK_LENGTH), 150, 20, 40, 5, '#');
			init_object(get_new_brick(BRICK, BRICK_LENGTH), 210, 15, 10, 10, '+');
			init_object(get_new_brick(BRICK, BRICK_LENGTH), 30, 10, 5, 3, '?');
			init_object(get_new_brick(BRICK, BRICK_LENGTH), 50, 10, 5, 3, '?');
			init_object(get_new_brick(BRICK, BRICK_LENGTH), 60, 5, 10, 3, '-');
			init_object(get_new_brick(BRICK, BRICK_LENGTH), 70, 5, 5, 3, '?');
			init_object(get_new_brick(BRICK, BRICK_LENGTH), 75, 5, 5, 3, '-');
			init_object(get_new_brick(BRICK, BRICK_LENGTH), 80, 5, 5, 3, '?');
			init_object(get_new_brick(BRICK, BRICK_LENGTH), 85, 5, 10, 3, '-');
			init_object(get_new_moving(moving, moving_length), 25, 10, 3, 2, 'o');
			init_object(get_new_moving(moving, moving_length), 80, 10, 3, 2, 'o');
			break;
    
		case 2:
			init_object(get_new_brick(BRICK, BRICK_LENGTH), 20, 20, 40, 5, '#');
			init_object(get_new_brick(BRICK, BRICK_LENGTH), 60, 15, 10, 5, '#');
			init_object(get_new_brick(BRICK, BRICK_LENGTH), 80, 20, 20, 5, '#');
			init_object(get_new_brick(BRICK, BRICK_LENGTH), 120, 15, 10, 10, '#');
			init_object(get_new_brick(BRICK, BRICK_LENGTH), 150, 20, 40, 5, '#');
			init_object(get_new_brick(BRICK, BRICK_LENGTH), 210, 15, 10, 10, '+');
			init_object(get_new_moving(moving, moving_length), 25, 10, 3, 2, 'o');
			init_object(get_new_moving(moving, moving_length), 80, 10, 3, 2, 'o');
			init_object(get_new_moving(moving, moving_length), 65, 10, 3, 2, 'o');
			init_object(get_new_moving(moving, moving_length), 120, 10, 3, 2, 'o');
			init_object(get_new_moving(moving, moving_length), 160, 10, 3, 2, 'o');
			init_object(get_new_moving(moving, moving_length), 175, 10, 3, 2, 'o');
			break;
			
		case 3:
			init_object(get_new_brick(BRICK, BRICK_LENGTH), 20, 20, 40, 5, '#');
			init_object(get_new_brick(BRICK, BRICK_LENGTH), 80, 20, 15, 5, '#');
			init_object(get_new_brick(BRICK, BRICK_LENGTH), 120, 15, 15, 10, '#');
			init_object(get_new_brick(BRICK, BRICK_LENGTH), 160, 10, 15, 15, '+');
			init_object(get_new_moving(moving, moving_length), 25, 10, 3, 2, 'o');
			init_object(get_new_moving(moving, moving_length), 50, 10, 3, 2, 'o');
			init_object(get_new_moving(moving, moving_length), 80, 10, 3, 2, 'o');
			init_object(get_new_moving(moving, moving_length), 90, 10, 3, 2, 'o');
			init_object(get_new_moving(moving, moving_length), 120, 10, 3, 2, 'o');
			init_object(get_new_moving(moving, moving_length), 130, 10, 3, 2, 'o');
			break;
	}
}

void delete_moving(S_OBJECT*& moving, std::size_t& moving_length, int i)
{
    if (i < 0 || i >= moving_length)
        return;
    
    moving[i] = moving[moving_length - 1];
    moving_length--;   
}

S_OBJECT* get_new_brick(S_OBJECT*& BRICK, std::size_t& BRICK_LENGTH)
{
    BRICK_LENGTH++;
    S_OBJECT* new_arr = new S_OBJECT[BRICK_LENGTH];
    if (BRICK != nullptr) {
        std::copy(BRICK, BRICK + BRICK_LENGTH - 1, new_arr);
        delete[] BRICK;
    }
    BRICK = new_arr;
    return BRICK + BRICK_LENGTH - 1;
}

S_OBJECT* get_new_moving(S_OBJECT*& moving, std::size_t& moving_length)
{
    moving_length++;
    S_OBJECT* new_arr = new S_OBJECT[moving_length];
    if (moving != nullptr) {
        std::copy(moving, moving + moving_length - 1, new_arr);
        delete[] moving;
    }
    moving = new_arr;
    return moving + moving_length - 1;
}

void horizon_move_map(S_OBJECT* MARIO, S_OBJECT*& BRICK, std::size_t& BRICK_LENGTH, 
					  S_OBJECT*& moving, std::size_t& moving_length, float dx)
{
    MARIO->x -= dx;
    for (int i = 0; i < BRICK_LENGTH; ++i)
        if (is_collision(*MARIO, BRICK[i])) {
            MARIO->x += dx;
            return;
        }
		
    MARIO->x += dx;
    
    for (int i = 0; i < BRICK_LENGTH; ++i)
        BRICK[i].x += dx;
	
    for (int i = 0; i < moving_length; ++i)
        moving[i].x += dx;
}

void horizon_move_object(S_OBJECT* obj, S_OBJECT* MARIO, 
						 S_OBJECT*& BRICK, std::size_t& BRICK_LENGTH, 
						 S_OBJECT*& moving, std::size_t& moving_length, 
						 int& LEVEL, int& MAX_LVL, int& SCORE)
{
    obj->x += obj->horiz_speed;
    
    for (int i = 0; i < BRICK_LENGTH; ++i)
        if (is_collision(*obj, BRICK[i])) {
            obj->x -= obj->horiz_speed;
            obj->horiz_speed = -obj->horiz_speed;
            return;
        }
    
    if (obj->c_type == 'o') {
        S_OBJECT tmp = *obj;
        vert_move_object(&tmp, MARIO, BRICK, BRICK_LENGTH, moving, moving_length, LEVEL, MAX_LVL, SCORE);
        if (tmp.is_fly == true) {
            obj->x -= obj->horiz_speed;
            obj->horiz_speed = -obj->horiz_speed;
        }
    }
}

void init_object(S_OBJECT* obj, float x_pos, float y_pos,
                 float o_width, float o_height, char in_type)
{
    set_object_pos(obj, x_pos, y_pos);
    obj->width = o_width;
    obj->height = o_height;
    obj->vert_speed = 0.0f;
    obj->c_type = in_type;
    obj->horiz_speed = 0.2f;
}

bool is_collision(S_OBJECT o1, S_OBJECT o2)
{
    return (((o1.x + o1.width) > o2.x)
            && (o1.x < (o2.x + o2.width))
            && ((o1.y + o1.height) > o2.y)
            && (o1.y < (o2.y + o2.height)));
}

bool is_pos_in_map(int x, int y)
{
    return ((x >= 0)
            && (x < MAP_WIDTH)
            && (y >= 0)
            && (y < MAP_HEIGHT));
}

void mario_collision(S_OBJECT* MARIO, S_OBJECT*& BRICK, std::size_t& BRICK_LENGTH,
					 S_OBJECT*& moving, std::size_t& moving_length,
					 int& LEVEL, int& MAX_LVL, int& SCORE)
{
    for (int i = 0; i < moving_length; ++i)
        if (is_collision(*MARIO, moving[i])) {
            if (moving[i].c_type == 'o') {
                if ((MARIO->is_fly == true) 
                    && (MARIO->vert_speed > 0) 
                    && (MARIO->y + MARIO->height < moving[i].y + moving[i].height * 0.5f)) {
                    
                    SCORE += 50;
                    delete_moving(moving, moving_length, i);
                    --i;
                    continue;
                }
                else
                    player_dead(MARIO, BRICK, BRICK_LENGTH, moving, moving_length, LEVEL, SCORE);
            }
            
            if (moving[i].c_type == '$') {
                SCORE += 100;
                delete_moving(moving, moving_length, i);
                --i;
                continue;
            }
        }
    MAX_LVL = 3;
}

void player_dead(S_OBJECT* MARIO, S_OBJECT*& BRICK, std::size_t& BRICK_LENGTH,
				 S_OBJECT*& moving, std::size_t& moving_length,
				 int& LEVEL, int& SCORE)
{
    std::system("color 4F");
    Sleep(500);
    create_level(MARIO, BRICK, BRICK_LENGTH, moving, moving_length, LEVEL, SCORE);
}

void put_object_on_map(S_OBJECT obj, char (&MAP)[MAP_HEIGHT][MAP_WIDTH + 1])
{
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

void put_score_on_map(int& SCORE, char (&MAP)[MAP_HEIGHT][MAP_WIDTH + 1])
{
    std::string score_str = "SCORE: " + std::to_string(SCORE);
    for (size_t i = 0; i < score_str.length() && (i + 5) < MAP_WIDTH; ++i)
        MAP[1][i + 5] = score_str[i];
}

void set_cur(int x, int y)
{
    COORD coord;
    coord.X = static_cast<SHORT>(x);
    coord.Y = static_cast<SHORT>(y);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void set_object_pos(S_OBJECT* obj, float x_pos, float y_pos)
{
    obj->x = x_pos;
    obj->y = y_pos;
}

void show_map(char (&MAP)[MAP_HEIGHT][MAP_WIDTH + 1])
{
    MAP[MAP_HEIGHT - 1][MAP_WIDTH - 1] = '\0';
    for (int j = 0; j < MAP_HEIGHT; ++j)
        std::cout << MAP[j];
}

void vert_move_object(S_OBJECT* obj, S_OBJECT* MARIO,
					  S_OBJECT*& BRICK, std::size_t& BRICK_LENGTH,
					  S_OBJECT*& moving, std::size_t& moving_length,
					  int& LEVEL, int& MAX_LVL, int& SCORE)
{
    obj->is_fly = true;
    obj->vert_speed += 0.05f;
    set_object_pos(obj, obj->x, obj->y + obj->vert_speed);
    
    for (int i = 0; i < BRICK_LENGTH; ++i)
        if (is_collision(*obj, BRICK[i])) {
            if (obj->vert_speed > 0)
                obj->is_fly = false;
            
            if ((BRICK[i].c_type == '?')
                && (obj->vert_speed < 0)
                && (obj == MARIO)) {
                    
                BRICK[i].c_type = '-';
                init_object(get_new_moving(moving, moving_length), BRICK[i].x, BRICK[i].y - 3.0f, 3.0f, 2.0f, '$');
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
                create_level(MARIO, BRICK, BRICK_LENGTH, moving, moving_length, LEVEL, SCORE);
            }
            break;
        }
}