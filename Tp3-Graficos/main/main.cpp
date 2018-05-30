#include <iostream>
using namespace std;
#include "allegro5\allegro.h"
#include "allegro5\allegro_image.h"
#include "allegro5\allegro_native_dialog.h"


enum KEYS {UP,DOWN,LEFT,RIGHT};

class enemy {
public:
	enemy() {};
	const float enemySPEED = 0.3;						//Variables del player//
	const int enemySize = 32;
	float enemyPOS_x;							//Variables del enemy//
	float enemyPOS_y;												 //
	float enemy_collisionBOX_x;								 //
	float enemy_collisionBOX_y;								 //
	float enemy_collisionBOX_w;										 //
	float enemy_collisionBOX_h;										 //
	bool movement;

};
int main(int argc, char **argv){

	bool gameover = false;							//Bool para el game loop

	const float playerSPEED = 0.3;						//Variables del player//
	float playerPOS_x = 0;												  //
	float playerPOS_y = 0;												  //
	float player_collisionBOX_x = playerPOS_x;							  //
	float player_collisionBOX_y = playerPOS_y;							  //
	float player_collisionBOX_w = 0;										  //
	float player_collisionBOX_h = 0;										  //
	bool arrayKeys[4] = { false,false,false,false };					  //

	enemy* bicho1 = new enemy();

	bicho1->enemyPOS_x = 0;
	bicho1->enemyPOS_y = 200;
	bicho1->enemy_collisionBOX_x = bicho1->enemyPOS_x;
	bicho1->enemy_collisionBOX_y = bicho1->enemyPOS_y;
	bicho1->enemy_collisionBOX_h = 0;
	bicho1->enemy_collisionBOX_w = 0;
	bicho1->movement = true;


	/*const float enemySPEED = 0.5;						//Variables del player//
	const int enemySize = 32;
	float enemyPOS_x = 0;							//Variables del enemy//
	float enemyPOS_y = 200;												 //
	float enemy_collisionBOX_x = enemyPOS_x;								 //
	float enemy_collisionBOX_y = enemyPOS_y;								 //
	float enemy_collisionBOX_w = 0;										 //
	float enemy_collisionBOX_h = 0;										 //
	bool movement = true;*/


	ALLEGRO_DISPLAY *display = NULL;				//Declaracion de un display
	ALLEGRO_BITMAP  *image = NULL;					//Declaracion de imagenes para el player y el enemigo//
	ALLEGRO_BITMAP  *image2 = NULL;																		 //

	if (!al_init()) {                                          //iniciacion de allegro
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	if (!al_init_image_addon()) {								//iniciacion de image
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 0;
	}

	display = al_create_display(640, 480);  //Creacion del display
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}

	image = al_load_bitmap("Personaje.png");							//Carga de imagenes y seteo de cajas de colisiones//
	if (!image) {																										  //						
		al_show_native_message_box(display, "Error", "Error", "Failed to load image!",									  //
			NULL, ALLEGRO_MESSAGEBOX_ERROR);																			  //
		al_destroy_display(display);																					  //
		return 0;																										  //
	}																													  //
	player_collisionBOX_h = al_get_bitmap_height(image);																  //
	player_collisionBOX_w = al_get_bitmap_width(image);																	  //
																														  //
	image2 = al_load_bitmap("Enemy.png");																				  //
	if (!image2) {																										  //
		al_show_native_message_box(display, "Error", "Error", "Failed to load image!",									  //
			NULL, ALLEGRO_MESSAGEBOX_ERROR);																			  //
		al_destroy_display(display);																					  //
		return 0;																										  //
	}																													  //
	bicho1->enemy_collisionBOX_h = al_get_bitmap_height(image2);																  //
	bicho1->enemy_collisionBOX_w = al_get_bitmap_width(image2);																	  //

	if (!al_install_keyboard())    //iniciacion del teclado
	{
		al_show_native_message_box(display, "Error", "Error", "Failed to load keyboard!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 0;
	}

	ALLEGRO_EVENT_QUEUE* event_queque = al_create_event_queue();
	ALLEGRO_EVENT events;										
	al_register_event_source(event_queque, al_get_keyboard_event_source());

	//Un DRAW fuera del GameLoop, para que dibuje todo la primera vez, sino sale todo blanco por el al_wait_for_event//
	al_draw_bitmap(image2, bicho1->enemyPOS_x, bicho1->enemyPOS_y, 0);
	al_draw_bitmap(image, playerPOS_x, playerPOS_y, 0);
	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));
	while (!gameover)
	{
		al_get_next_event(event_queque, &events);
		
		//INPUT//
		if (events.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (events.keyboard.keycode)
			{
			case ALLEGRO_KEY_DOWN:
				arrayKeys[DOWN] = true;
				break;
			case ALLEGRO_KEY_UP:
				arrayKeys[UP] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				arrayKeys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				arrayKeys[RIGHT] = true;
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
				arrayKeys[DOWN] = false;
				break;
			case ALLEGRO_KEY_UP:
				arrayKeys[UP] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				arrayKeys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				arrayKeys[RIGHT] = false;
				break;
			}
		}
		if (bicho1->enemyPOS_x >= 640 - bicho1->enemySize)
		{
			bicho1->movement = false;
		}
		if (bicho1->enemyPOS_x <= 0)
		{
			bicho1->movement = true;
		}
		if (bicho1->movement == true)
		{
			bicho1->enemyPOS_x += bicho1->enemySPEED;
		}
		if (bicho1->movement == false)
		{
			bicho1->enemyPOS_x -= bicho1->enemySPEED;
		}
		
		cout << bicho1->enemyPOS_x << endl;
		//UPDATE//
		playerPOS_x += arrayKeys[RIGHT] * playerSPEED;
		playerPOS_x -= arrayKeys[LEFT] * playerSPEED;
		playerPOS_y += arrayKeys[DOWN] * playerSPEED;
		playerPOS_y -= arrayKeys[UP] * playerSPEED;

		player_collisionBOX_x = player_collisionBOX_w /2;
		player_collisionBOX_y = player_collisionBOX_h /2;

		bicho1->enemy_collisionBOX_x = bicho1->enemy_collisionBOX_w /2;
		bicho1->enemy_collisionBOX_y = bicho1->enemy_collisionBOX_h /2;

		if (playerPOS_x + player_collisionBOX_x > bicho1->enemyPOS_x - bicho1->enemy_collisionBOX_x &&
			playerPOS_x - player_collisionBOX_x < bicho1->enemyPOS_x + bicho1->enemy_collisionBOX_x &&
			playerPOS_y + player_collisionBOX_y > bicho1->enemyPOS_y - bicho1->enemy_collisionBOX_y &&
			playerPOS_y - player_collisionBOX_y < bicho1->enemyPOS_y + bicho1->enemy_collisionBOX_y)
		{
			gameover = true;
		}

		//DRAW//
		al_draw_bitmap(image2, bicho1->enemyPOS_x, bicho1->enemyPOS_y, 0);
		al_draw_bitmap(image, playerPOS_x, playerPOS_y, 0);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}

	al_destroy_display(display);
	al_destroy_bitmap(image);
	al_destroy_bitmap(image2);
	al_destroy_event_queue(event_queque);

	return 0;

}

