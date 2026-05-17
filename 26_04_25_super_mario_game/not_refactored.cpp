#include <stdio.h>
#include <stdio.h>

#include <math.h>
#include <windows.h>

#define MAP_WIDTH 80
#define MAP_HEIGHT 25

struct S_OBJECT {
	float x,y;
	float width, height;
	float vert_speed;
	bool is_fly;
	char c_type;
	float horiz_speed;
};

char MAP[MAP_HEIGHT][MAP_WIDTH+1];
S_OBJECT MARIO;
S_OBJECT *BRICK = NULL;
int BRICK_LENGTH;

S_OBJECT *moving = NULL;
int moving_length;

int LEVEL = 1;
int SCORE;
int MAX_LVL;

void create_level(int lvl);

void clear_map(){
	
	for (int i = 0; i < MAP_WIDTH; i++)
		MAP[0][i] = ' ';
	
	MAP[0][MAP_WIDTH] = '\0';
	
	for (int j = 0; j < MAP_HEIGHT; j++)
		sprintf(MAP[j], MAP[0]);
}

void show_map() {
	MAP[MAP_HEIGHT - 1][MAP_WIDTH - 1] = '\0';
	for (int j = 0; j < MAP_HEIGHT; j++)
		printf("%s", MAP[j]);
}


void set_object_pos(S_OBJECT *obj, float x_pos, float y_pos){
	(*obj).x = x_pos;
	(*obj).y = y_pos;
}

void init_object(S_OBJECT *obj, float x_pos, float y_pos, float o_width, float o_height, char in_type){
	set_object_pos(obj, x_pos, y_pos);
	(*obj).width = o_width;
	(*obj).height = o_height;
	(*obj).vert_speed = 0;
	(*obj).c_type = in_type;
	(*obj).horiz_speed = 0.2;
}

void player_dead(){
	
	system("color 4F");
	Sleep(500);
	create_level(LEVEL);
}

bool is_collision(S_OBJECT o1, S_OBJECT o2);
S_OBJECT *get_new_moving();

void vert_move_object(S_OBJECT *obj){
	
	(*obj).is_fly = true;
	(*obj).vert_speed += 0.05;
	set_object_pos(obj, (*obj).x, (*obj).y + (*obj).vert_speed);
	
	for (int i = 0; i < BRICK_LENGTH; i++)
		if (is_collision(*obj, BRICK[i])){
			if (obj[0].vert_speed > 0)
				obj[0].is_fly = false;
			
			if ((BRICK[i].c_type == '?') && (obj[0].vert_speed < 0) && (obj == &MARIO)) {
				BRICK[i].c_type = '-';
				init_object(get_new_moving(), BRICK[i].x, BRICK[i].y-3, 3, 2, '$');
				moving[moving_length - 1].vert_speed = -0.7;
			}
			
			(*obj).y -= (*obj).vert_speed;
			(*obj).vert_speed = 0;
			if (BRICK[i].c_type == '+') {
				LEVEL++;
				if (LEVEL > MAX_LVL)
					LEVEL = 1;
				system("color 2F");
				Sleep(500);
				create_level(LEVEL);
			}
			break;
		}
	
}

void delete_moving(int i) {
	if (i < 0 || i >= moving_length) return;
    
    moving[i] = moving[moving_length - 1];
    moving_length--;   
}

void mario_collision() {
	for (int i = 0; i < moving_length; i++)
		if (is_collision(MARIO, moving[i])) {
			if (moving[i].c_type == 'o') {
				if ((MARIO.is_fly == true) 
					&& (MARIO.vert_speed > 0) 
				&& (MARIO.y + MARIO.height < moving[i].y + moving[i].height*0.5)) {
					
					SCORE += 50;
					delete_moving(i);
					i--;
					continue;
				}
				else
					player_dead();
			}
			
			if (moving[i].c_type == '$'){
				SCORE += 100;
				delete_moving(i);
				i--;
				continue;
			}
		}
	MAX_LVL = 3;
}

void horizon_move_object(S_OBJECT *obj) {
	obj[0].x += obj[0].horiz_speed;
	
	for (int i = 0; i < BRICK_LENGTH; i++)
		if(is_collision(obj[0], BRICK[i])) {
			obj[0].x -= obj[0].horiz_speed;
			obj[0].horiz_speed = -obj[0].horiz_speed;
			return;
		}
	
	if (obj[0].c_type == 'o') {
		S_OBJECT tmp = *obj;
		vert_move_object(&tmp);
		if (tmp.is_fly == true) {
			obj[0].x -= obj[0].horiz_speed;
			obj[0].horiz_speed = -obj[0].horiz_speed;
		}
	}
}

bool is_pos_in_map(int x, int y) {
	return ((x >= 0) && (x < MAP_WIDTH) && (y >= 0) && (y < MAP_HEIGHT));
}

void put_object_on_map(S_OBJECT obj) {
	int ix = (int)round(obj.x);
	int iy = (int)round(obj.y);
	int i_width = (int)round(obj.width);
	int i_height = (int)round(obj.height);
	
	for (int i = ix; i < (ix+i_width); i++){
		for (int j = iy; j < (iy+i_height); j++)
			if (is_pos_in_map(i, j))
				MAP[j][i] = obj.c_type;
	}
}

void set_cur (int x, int y){
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void horizon_move_map(float dx) {
	
	MARIO.x -= dx;
	for (int i  = 0; i < BRICK_LENGTH; i++)
		if (is_collision(MARIO, BRICK[i])) {
			MARIO.x += dx;
			return;
		}
	MARIO.x += dx;
	
	for (int i = 0; i < BRICK_LENGTH; i++)
		BRICK[i].x += dx;
	for (int i = 0; i < moving_length; i++)
		moving[i].x += dx;
}

bool is_collision(S_OBJECT o1, S_OBJECT o2) {
	return (((o1.x + o1.width) > o2.x) && (o1.x < (o2.x + o2.width)) &&
			((o1.y + o1.height) > o2.y) && (o1.y < (o2.y + o2.height)));
}

S_OBJECT *get_new_brick() {
	BRICK_LENGTH++;
	BRICK = (S_OBJECT*)realloc(BRICK, sizeof(*BRICK)*BRICK_LENGTH);
	return BRICK + BRICK_LENGTH - 1;
}

S_OBJECT *get_new_moving() {
	moving_length++;
	moving = (S_OBJECT*)realloc(moving, sizeof(*moving)*moving_length);
	return moving + moving_length - 1;
}

void put_score_on_map(){
	char c[30];
	sprintf(c, "SCORE: %d", SCORE);
	int len = strlen(c);
	for (int i = 0; i < len; i++)
		MAP[1][i+5] = c[i];
}

void create_level(int lvl) {
	
	system("color 9F");
	
	BRICK_LENGTH = 0;
	BRICK = (S_OBJECT*)realloc(BRICK, 0);
	moving_length = 0;
	moving = (S_OBJECT*)realloc(moving, 0);
	
	init_object(&MARIO, 39, 10, 3, 3, '@');
	SCORE = 0;
	
	
	if (lvl == 1) {
		init_object(get_new_brick(), 20, 20, 40, 5, '#');
			init_object(get_new_brick(), 30, 10, 5, 3, '?');
			init_object(get_new_brick(), 50, 10, 5, 3, '?');
		init_object(get_new_brick(), 60, 15, 40, 10, '#');
			init_object(get_new_brick(), 60, 5, 10, 3, '-');
			init_object(get_new_brick(), 70, 5, 5, 3, '?');
			init_object(get_new_brick(), 75, 5, 5, 3, '-');
			init_object(get_new_brick(), 80, 5, 5, 3, '?');
			init_object(get_new_brick(), 85, 5, 10, 3, '-');
		init_object(get_new_brick(), 100, 20, 20, 5, '#');
		init_object(get_new_brick(), 120, 15, 10, 10, '#');
		init_object(get_new_brick(), 150, 20, 40, 5, '#');
		init_object(get_new_brick(), 210, 15, 10, 10, '+');
		
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

int main()
{
	create_level(LEVEL);
	
	do {
		clear_map();
		if((MARIO.is_fly == false) && (GetKeyState(VK_SPACE) < 0))
			MARIO.vert_speed = -1;
		if (GetKeyState('A') < 0)
			horizon_move_map(1);
		if (GetKeyState('D') < 0)
			horizon_move_map(-1);
		
		if (MARIO.y > MAP_HEIGHT)
			player_dead();
		
		vert_move_object(&MARIO);
		mario_collision();
		
		for(int i = 0; i < BRICK_LENGTH; i++)
			put_object_on_map(BRICK[i]);
		
		for(int i = 0; i < moving_length; i++){
			vert_move_object(moving+i);
			horizon_move_object(moving+i);
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