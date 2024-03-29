//allegro headers
#include<allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>

//our headers
#include"platform.h"
#include"barrel.h"
#include"globals.h"
#include"player.h"
#include"gameObject.h"

//cpp libraries
#include<iostream>
#include<vector>
using namespace std;

int main() {

	//set up allegro
	al_init();
	al_install_keyboard();
	al_init_primitives_addon();
	al_init_image_addon();

	//set up gamescreen, event queue, and timer
	ALLEGRO_DISPLAY* display = al_create_display(SCREEN_W, SCREEN_H);
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
	ALLEGRO_BITMAP* picture = al_load_bitmap("platform.jpg");
	ALLEGRO_BITMAP* picture2 = al_load_bitmap("barrel.png");
	al_convert_mask_to_alpha(picture2, al_map_rgb(255, 255, 255));
	al_start_timer(timer);

	//game variables
	bool key[4] = { false, false, false, false }; //holds key clicks
	bool redraw = true; //variable needed for render section
	bool doexit = false; //hadles game loop

	//tell event queue what to look for
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	//create all the game objects

	//vector to hold all the game objects
	vector<gameObject*> objects;
	vector<gameObject*>::iterator iter;

	//PLATFORMS
	//create bottom row of platforms
	for (int i = 0; i < 5; i++) {
		platform* newPlat = new platform(i * PLATFORM_WIDTH, SCREEN_H - PLATFORM_HEIGHT, picture); //left side is flat
		objects.push_back(newPlat);
	}
	for (int i = 0; i < 5; i++) {
		platform* newPlat = new platform(i * PLATFORM_WIDTH + SCREEN_W / 2, (SCREEN_H - PLATFORM_HEIGHT) - i * 5, picture); //right side steps up
		objects.push_back(newPlat);
	}

	//second row
	for (int i = 0; i < 8; i++) {
		platform* newPlat = new platform(i * PLATFORM_WIDTH, 600 + 1 * 5, picture);
		objects.push_back(newPlat);
	}

	//middle row
	for (int i = 0; i < 7; i++) {
		platform* newPlat = new platform(i * PLATFORM_WIDTH + SCREEN_W / 2 - 100, (SCREEN_H - PLATFORM_HEIGHT - 300) - i * 5, picture);
		objects.push_back(newPlat);
	}

	//top row
	for (int i = 0; i < 8; i++) {
		platform* newPlat = new platform(i * PLATFORM_WIDTH, 300 + 1 * 5, picture);
		objects.push_back(newPlat);
	}

	//barrels
	barrel* b1 = new barrel(100, 100, picture2);
	barrel* b2 = new barrel(rand() % 500 - 1000, rand() % 500 - 1000, picture2);
	barrel* b3 = new barrel(rand() % 500 - 1000, rand() % 500 - 1000, picture2);
	barrel* b4 = new barrel(rand() % 500 - 1000, rand() % 500 - 1000, picture2);
	barrel* b5 = new barrel(rand() % 500 - 1000, rand() % 500 - 1000, picture2);
	objects.push_back(b1);
	objects.push_back(b2);
	objects.push_back(b3);
	objects.push_back(b4);
	objects.push_back(b5);

	//player
	player* p1 = new player();
	objects.push_back(p1);

	while (!doexit) { //game loop!

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//timer (physics) section
		if (ev.type == ALLEGRO_EVENT_TIMER) {

			//keyboard movement
			if (key[KEY_UP]) {
				p1->jump();
			}

			if (key[KEY_LEFT]) {
				p1->moveLeft();
			}

			if (key[KEY_RIGHT]) {
				p1->moveRight();
			}

			//move ALL gmae objects
			for (iter = objects.begin(); iter != objects.end(); iter++) {
				(*iter)->move(objects);
			}

			redraw = true;
		}
		//keyboard and screen sections
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;
			}

		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;
			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}
		}

		//render section
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			al_clear_to_color(al_map_rgb(0, 0, 0)); //wipe screen black between drawing (without this things smear)

			//draw ALL game objects
			for (iter = objects.begin(); iter != objects.end(); iter++) {
				(*iter)->draw();
			}

			al_flip_display(); //flip everything from memory to gamescreen
		} //end render
	} //end of game loop

	//clean up memory
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	return 0;
} //end main
