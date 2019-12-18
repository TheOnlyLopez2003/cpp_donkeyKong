#pragma once
#include<allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include<vector>
#include"gameObject.h"
using namespace std; //needed for vectors!

class barrel : public gameObject {
private:
	int dir;
	int angle;

public:
	barrel(int x, int y, ALLEGRO_BITMAP* image101);
	void draw();
	void move(vector<gameObject*>stuff);
};
