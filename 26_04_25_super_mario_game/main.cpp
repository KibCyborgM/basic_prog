#include <stdio.h>
#include <stdio.h>

#include <math.h>
#include <windows.h>

#define mapWidth 80
#define mapHeight 25

struct SObject {
	float x,y;
	float width, height;
	float vertSpeed;
	bool IsFly;
};

char map[mapHeight][mapWidth+1];
SObject mario;
SObject brick[1];

void ClearMap(){
	
	for (int i = 0; i < mapWidth; i++)
		map[0][i] = '.';
	
	map[0][mapWidth] = '\0';
	
	for (int j = 0; j < mapHeight; j++)
		sprintf(map[j], map[0]);
}

void ShowMap() {
	map[mapHeight - 1][mapWidth - 1] = '\0';
	for (int j = 0; j < mapHeight; j++)
		printf("%s", map[j]);
}


void SetObjectPos(SObject *obj, float xPos, float yPos){
	(*obj).x = xPos;
	(*obj).y = yPos;
}

void InitObject(SObject *obj, float xPos, float yPos, float oWidth, float oHeight){
	SetObjectPos(obj, xPos, yPos);
	(*obj).width = oWidth;
	(*obj).height = oHeight;
	(*obj).vertSpeed = 0;
}

bool IsCollision(SObject o1, SObject o2);

void VertMoveObject(SObject *obj){
	
	(*obj).IsFly = true;
	(*obj).vertSpeed += 0.05;
	SetObjectPos(obj, (*obj).x, (*obj).y + (*obj).vertSpeed);
	if (IsCollision(*obj, brick[0])){
		(*obj).y -= (*obj).vertSpeed;
		(*obj).vertSpeed = 0;
		(*obj).IsFly = false;
	}
	
}

bool IsPosInMap(int x, int y) {
	return ((x >= 0) && (x < mapWidth) && (y >= 0) && (y < mapHeight));
}

void PuTObjectOnMap(SObject obj) {
	int ix = (int)round(obj.x);
	int iy = (int)round(obj.y);
	int iWidth = (int)round(obj.width);
	int iHeight = (int)round(obj.height);
	
	for (int i = ix; i < (ix+iWidth); i++){
		for (int j = iy; j < (iy+iHeight); j++)
			if (IsPosInMap(i, j))
				map[j][i] = '@';
	}
	map[iy][ix] = '@';
}

void setCur (int x, int y){
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

bool IsCollision(SObject o1, SObject o2) {
	return (((o1.x + o1.width) > o2.x) && (o1.x < (o2.x + o2.width)) &&
			((o1.y + o1.height) > o2.y) && (o1.y < (o2.y + o2.height)));
}

int main()
{
	InitObject(&mario, 39, 10, 3, 3);
	InitObject(brick, 20, 20, 40, 5);
	
	do {
		ClearMap();
		if((mario.IsFly == false) && (GetKeyState(VK_SPACE) < 0))
			mario.vertSpeed = -1;
		
		VertMoveObject(&mario);
		PuTObjectOnMap(brick[0]);
		PuTObjectOnMap(mario);
		
		
		setCur(0, 0);
		ShowMap();
		Sleep(10);
	} while (GetKeyState(VK_ESCAPE) >= 0);
	return 0;
}