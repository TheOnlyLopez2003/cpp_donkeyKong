#pragma once
#include<allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include"gameObject.h"

class platform : public gameObject {
public:
	platform(int x, int y, ALLEGRO_BITMAP* image1010);
	void draw();
};
