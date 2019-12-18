#include"platform.h"
#include"globals.h"

platform::platform(int x, int y, ALLEGRO_BITMAP* image1010) {

	xPos = x;
	yPos = y;
	pic = image1010;
	ID = PLATFORM;

}

void platform::draw() {

	al_draw_bitmap(pic, xPos, yPos, NULL);

}
