#pragma once
#include"globals.h"
#include"gameObject.h"

class player : public gameObject {
private:
	double xVel;
	double yVel;
	bool canJump;

public:
	player();
	void move(vector<gameObject*>stuff);
	void moveLeft();
	void moveRight();
	void jump();
	void draw();
	int verticalCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2, int ydir);
};
