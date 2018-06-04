#include <iostream>
#include "allegro5\allegro.h"
#include "allegro5\allegro_image.h"
#include "allegro5\allegro_native_dialog.h"
using namespace std;


enum KEYS { UP, DOWN, LEFT, RIGHT, SPACEBAR };

class enemy {
public:
	enemy() {};
	const float enemySPEED = 0.08;						
	const int enemySize = 32;
	float enemyPOS_x ;							
	float enemyPOS_y;												 
	float enemy_collisionBOX_x;								 
	float enemy_collisionBOX_y;								
	float enemy_collisionBOX_w;										 
	float enemy_collisionBOX_h;										 
	bool movement;

};
class bullet {
public:
	bullet() {};
	const float BulletSpeed = 0.05;
	const int BulletSize = 4;
	bool bulletUp;
	bool bulletDown;
	bool bulletRight;
	bool bulletLeft;
	float BulletPOS_x;							
	float BulletPOS_y;
	float Bullet_collisionBOX_x;								 
	float Bullet_collisionBOX_y;
	float Bullet_collisionBOX_w;
	float Bullet_collisionBOX_h;
	
};
int main(int argc, char **argv){

	bool gameover = false;						

	const float playerSPEED = 0.03;					
	float playerPOS_x = 0;												  
	float playerPOS_y = 0;												  
	float player_collisionBOX_x = playerPOS_x;							  
	float player_collisionBOX_y = playerPOS_y;							  
	float player_collisionBOX_w = 0;										  
	float player_collisionBOX_h = 0;	
	int playerSize = 32;
	bool playerUp = true;
	bool playerDown = false;
	bool playerLeft = false;
	bool playerRight = false;
	
	int cantEnemys = 0;
	bool BoolBullets = false;
	//
	bool arrayKeys[4] = { false,false,false,false };					  
	enemy* bicho1[10];
	bullet* bala;
	for (int i = 0; i < 10; i++)
	{
		bicho1[i] = new enemy();

		bicho1[i]->enemyPOS_x = i * 20;
		bicho1[i]->enemyPOS_y = i * 40 + 40;
		bicho1[i]->enemy_collisionBOX_x = bicho1[i]->enemyPOS_x;
		bicho1[i]->enemy_collisionBOX_y = bicho1[i]->enemyPOS_y;
		bicho1[i]->enemy_collisionBOX_h = 0;
		bicho1[i]->enemy_collisionBOX_w = 0;
		bicho1[i]->movement = true;
		cantEnemys++;
	}
	


	/*const float enemySPEED = 0.5;						//Variables del player//
	const int enemySize = 32;
	float enemyPOS_x = 0;							//Variables del enemy//
	float enemyPOS_y = 200;												 //
	float enemy_collisionBOX_x = enemyPOS_x;								 //
	float enemy_collisionBOX_y = enemyPOS_y;								 //
	float enemy_collisionBOX_w = 0;										 //
	float enemy_collisionBOX_h = 0;										 //
	bool movement = true;*/


	ALLEGRO_DISPLAY *display = NULL;				
	ALLEGRO_BITMAP  *image = NULL;					
	ALLEGRO_BITMAP  *image2 = NULL;																		 
	ALLEGRO_BITMAP  *bulletImage = NULL;

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
		al_show_native_message_box(display, "Error", "Error", "Failed to load player!",									  
			NULL, ALLEGRO_MESSAGEBOX_ERROR);																			  
		al_destroy_display(display);																					  
		return 0;																										  
	}																													  
	player_collisionBOX_h = al_get_bitmap_height(image);																  
	player_collisionBOX_w = al_get_bitmap_width(image);																	  
																														  
	image2 = al_load_bitmap("Enemy.png");																				  
	if (!image2) {																										  
		al_show_native_message_box(display, "Error", "Error", "Failed to load enemy!",									  
			NULL, ALLEGRO_MESSAGEBOX_ERROR);																			  
		al_destroy_display(display);																					  
		return 0;																										  
	}		

	bulletImage = al_load_bitmap("Bullet.png");																				  
	if (!bulletImage) {																										  
		al_show_native_message_box(display, "Error", "Error", "Failed to load bullet!",									  
			NULL, ALLEGRO_MESSAGEBOX_ERROR);																			  
		al_destroy_display(display);																					  
		return 0;																										  
	}
	for (int i = 0; i < cantEnemys; i++)
	{
		bicho1[i]->enemy_collisionBOX_h = al_get_bitmap_height(image2);
		bicho1[i]->enemy_collisionBOX_w = al_get_bitmap_width(image2);
	}
	

	if (!al_install_keyboard())    //iniciacion del teclado
	{
		al_show_native_message_box(display, "Error", "Error", "Failed to load keyboard!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 0;
	}

	ALLEGRO_EVENT_QUEUE* event_queque = al_create_event_queue();
	ALLEGRO_EVENT events;										
	al_register_event_source(event_queque, al_get_keyboard_event_source());

	
	
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
				playerDown = true;
				playerUp = false;
				playerLeft = false;
				playerRight = false;
				break;
			case ALLEGRO_KEY_UP:
				arrayKeys[UP] = true;
				playerDown = false;
				playerUp = true;
				playerLeft = false;
				playerRight = false;
				break;
			case ALLEGRO_KEY_LEFT:
				arrayKeys[LEFT] = true;
				playerDown = false;
				playerUp = false;
				playerLeft = true;
				playerRight = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				arrayKeys[RIGHT] = true;
				playerDown = false;
				playerUp = false;
				playerLeft = false;
				playerRight = true;
				break;
			case ALLEGRO_KEY_ESCAPE:
				gameover = true;
				break;
			case ALLEGRO_KEY_SPACE:	
				bala = new bullet();
				
				BoolBullets = true;		
				bala->BulletPOS_x = playerPOS_x + (playerSize / 2);
				bala->BulletPOS_y = playerPOS_y + (playerSize / 2);
				bala->bulletUp = playerUp;
				bala->bulletDown = playerDown;
				bala->bulletLeft = playerLeft;
				bala->bulletRight = playerRight;
				bala->Bullet_collisionBOX_x = bala->BulletPOS_x;
				bala->Bullet_collisionBOX_y = bala->BulletPOS_y;
				bala->Bullet_collisionBOX_h = al_get_bitmap_height(bulletImage);
				bala->Bullet_collisionBOX_w = al_get_bitmap_width(bulletImage);
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
	
		if (BoolBullets)
		{
			if (bala->bulletDown)
			{
				bala->BulletPOS_y += bala->BulletSpeed;
			}
			if (bala->bulletUp)
			{
				bala->BulletPOS_y -= bala->BulletSpeed;
			}
			if (bala->bulletLeft)
			{
				bala->BulletPOS_x -= bala->BulletSpeed;
			}
			if (bala->bulletRight)
			{
				bala->BulletPOS_x += bala->BulletSpeed;
			}
		}
		/*
		for (int i = 0; i < cantEnemys; i++)
		{
			if (bicho1[i]->enemyPOS_x >= 640 - bicho1[i]->enemySize)
			{
				bicho1[i]->movement = false;
			}
			if (bicho1[i]->enemyPOS_x <= 0)
			{
				bicho1[i]->movement = true;
			}
			if (bicho1[i]->movement == true)
			{
				bicho1[i]->enemyPOS_x += bicho1[i]->enemySPEED;
			}
			if (bicho1[i]->movement == false)
			{
				bicho1[i]->enemyPOS_x -= bicho1[i]->enemySPEED;
			}
		}*/

		
		//UPDATE//
		playerPOS_x += arrayKeys[RIGHT] * playerSPEED;
		playerPOS_x -= arrayKeys[LEFT] * playerSPEED;
		playerPOS_y += arrayKeys[DOWN] * playerSPEED;
		playerPOS_y -= arrayKeys[UP] * playerSPEED;

		player_collisionBOX_x = player_collisionBOX_w /2;
		player_collisionBOX_y = player_collisionBOX_h /2;
		for (int i = 0; i < cantEnemys; i++)
		{
			bicho1[i]->enemy_collisionBOX_x = bicho1[i]->enemy_collisionBOX_w / 2;
			bicho1[i]->enemy_collisionBOX_y = bicho1[i]->enemy_collisionBOX_h / 2;

			if (playerPOS_x + player_collisionBOX_x > bicho1[i]->enemyPOS_x - bicho1[i]->enemy_collisionBOX_x &&
				playerPOS_x - player_collisionBOX_x < bicho1[i]->enemyPOS_x + bicho1[i]->enemy_collisionBOX_x &&
				playerPOS_y + player_collisionBOX_y > bicho1[i]->enemyPOS_y - bicho1[i]->enemy_collisionBOX_y &&
				playerPOS_y - player_collisionBOX_y < bicho1[i]->enemyPOS_y + bicho1[i]->enemy_collisionBOX_y)
			{
				//gameover = true;

			}

			if( BoolBullets == true && 
				(bala->BulletPOS_x + 4/*bala->Bullet_collisionBOX_x*/ > bicho1[i]->enemyPOS_x - bicho1[i]->enemy_collisionBOX_x &&
				bala->BulletPOS_x - 4/*bala->Bullet_collisionBOX_x*/ < bicho1[i]->enemyPOS_x + bicho1[i]->enemy_collisionBOX_x &&
				bala->BulletPOS_y + 4/*bala->Bullet_collisionBOX_y*/ > bicho1[i]->enemyPOS_y - bicho1[i]->enemy_collisionBOX_y &&
				bala->BulletPOS_y - 4/*bala->Bullet_collisionBOX_y*/ < bicho1[i]->enemyPOS_y + bicho1[i]->enemy_collisionBOX_y))
			{
				delete bicho1[i];
				delete bala;
				cout << i << endl;
		//		cantEnemys--;
				BoolBullets = false;
			}
		}
		//DRAW//

		for (int i = 0; i < cantEnemys; i++)
		{
			if (bicho1[i] != NULL)
				al_draw_bitmap(image2, bicho1[i]->enemyPOS_x, bicho1[i]->enemyPOS_y, 0);
		}
		if (BoolBullets == true)
		{
			al_draw_bitmap(bulletImage, bala->BulletPOS_x, bala->BulletPOS_y, 0);
		}
		al_draw_bitmap(image, playerPOS_x, playerPOS_y, 0);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}


	al_destroy_display(display);
	al_destroy_bitmap(image);
	al_destroy_bitmap(image2);
	al_destroy_event_queue(event_queque);
	//delete[] bicho1;

	return 0;
}

