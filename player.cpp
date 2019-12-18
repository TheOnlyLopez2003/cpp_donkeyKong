#include"player.h"
#include"globals.h"
#include<allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>

player::player() { //constructor

	//position of player
	xPos = 100;
	yPos = SCREEN_H - 50;

	//player velocity
	xVel = 0;
	yVel = 0;

	isOnGround = false;
	canJump = false;
	ID = PLAYER;

}

void player::moveLeft() {

	xVel--;

}

void player::moveRight() {

	xVel++;

}

void player::jump() {

	if (canJump) {
		yVel = -10;
	}

}

void player::draw() {

	al_draw_filled_rectangle(xPos, yPos, xPos + 30, yPos + 30, al_map_rgb(50, 120, 10));

}

void player::move(vector<gameObject*>stuff) {

	//deal with platform collision
	vector<gameObject*>::iterator iter;
	int x;
	int y;

	for (iter = stuff.begin(); iter != stuff.end(); iter++) {

		if ((*iter)->getID() == PLATFORM) { //only worry about colliding with platforms here...

			x = (*iter)->getX();
			y = (*iter)->getY();

			if (verticalCollision(xPos, yPos, 32, 32, (*iter)->getX(), (*iter)->getY(), PLATFORM_WIDTH, PLATFORM_HEIGHT, yVel) == 2) {
				yVel = -1.0;
				isOnGround = true;
			}
			if (verticalCollision(xPos, yPos, 32, 32, (*iter)->getX(), (*iter)->getY(), PLATFORM_WIDTH, PLATFORM_HEIGHT, yVel) == 1) {
				yVel = 0.0;
				isOnGround = true;
			}

		}

	}

	//update player position by adding velocity
	xPos += xVel;
	yPos += yVel;

	//friction (slippy slidey)
	xVel *= .7; //the smaller this number, the greater the friction

	//gravity (pull down if you're up in the air)
	if (isOnGround == false) {
		yVel += .4; //falling speed
		canJump = false; //turns off flying/double jumping
	}
	else {
		yVel = 0; //stop downward movement if we're on the ground
		canJump = true;
	}

	//check if you're falling (so gravity can work)
	if (yPos + 30 > SCREEN_H) {
		isOnGround = true;
	}
	else {
		isOnGround = false;
	}

	//set terminal velocity (don't fall too fast)
	if (yVel > 5) {
		yVel = 5;
	}

	//bounds checking (don't go off screen)
	if (xPos < 0) {
		xPos = 0;
	}
	if (xPos + 32 > SCREEN_W) {
		xPos = SCREEN_W - 32;
	}
}

//collision function that differs based on how close your feet are to the ground, allowing you to "walk" up shallow stairs
int player::verticalCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2, int yDir) {

	if ((yDir >= 0) &&
		(x1 + w1 > x2) &&
		(x1 < x2 + w2) &&
		(y1 + h1 + 4 > y2) && //the 4 means you're too close to the ground
		(y1 < y2)) {
		//cout << "adjusting up";
		return 2;
	}

	else if ((yDir >= 0) &&
		(x1 + w1 > x2) &&
		(x1 < x2 + w2) &&
		(y1 + h1 + 6 > y2) && //the 6 means you're not too close and don't need to adjust the player's position up
		(y1 < y2)) {
		//cout << "stable yPos";
		return 1;
	}

	else {
		return false;
	}

}
