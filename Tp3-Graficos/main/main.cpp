#include <iostream>
#include "allegro5\allegro.h"
#include "allegro5\allegro_image.h"
#include "allegro5\allegro_native_dialog.h"

int playerPOS_x = 0;
int playerPOS_y = 0;
int playerSPEED = 5;

bool arroyKeys[4] = { false,false,false,false };

enum KEYS {UP,DOWN,LEFT,RIGHT};


int main(int argc, char **argv){

	bool gameover = false;

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_BITMAP  *image = NULL;

	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	if (!al_init_image_addon()) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 0;
	}

	display = al_create_display(640, 480);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}

	image = al_load_bitmap("Personaje.png");
	if (!image) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		return 0;
	}

	al_install_keyboard();
	ALLEGRO_EVENT_QUEUE* event_queque = al_create_event_queue();
	al_register_event_source(event_queque, al_get_keyboard_event_source());

	while (!gameover)
	{
		ALLEGRO_EVENT events;

		al_draw_bitmap(image, playerPOS_x, playerPOS_y, 0);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));

		al_wait_for_event(event_queque, &events);

		if (events.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (events.keyboard.keycode)
			{
			case ALLEGRO_KEY_DOWN:
				arroyKeys[DOWN] = true;
				break;
			case ALLEGRO_KEY_UP:
				arroyKeys[UP] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				arroyKeys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				arroyKeys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_ESCAPE:
				gameover = true;
				break;
			}
		}
		else if (events.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (events.keyboard.keycode)
			{
			case ALLEGRO_KEY_DOWN:
				arroyKeys[DOWN] = false;
				break;
			case ALLEGRO_KEY_UP:
				arroyKeys[UP] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				arroyKeys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				arroyKeys[RIGHT] = false;
				break;
			}
		}

		playerPOS_x += arroyKeys[RIGHT] * playerSPEED;
		playerPOS_x -= arroyKeys[LEFT] * playerSPEED;
		playerPOS_y += arroyKeys[DOWN] * playerSPEED;
		playerPOS_y -= arroyKeys[UP] * playerSPEED;
	}

	al_destroy_display(display);
	al_destroy_bitmap(image);
	al_destroy_event_queue(event_queque);

	return 0;

}