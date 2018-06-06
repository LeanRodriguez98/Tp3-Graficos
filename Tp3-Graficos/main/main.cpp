#include <iostream>
#include <time.h>
#include "allegro5\allegro.h"
#include "allegro5\allegro_image.h"
#include "allegro5\allegro_native_dialog.h"
#include "allegro5\allegro_acodec.h"
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>

using namespace std;


enum KEYS { UP, DOWN, LEFT, RIGHT, SPACEBAR };

class enemy {
public:
	enemy() {};
	const float enemySPEED = 0.05;						
	const int enemySize = 32;
	float enemyPOS_x;							
	float enemyPOS_y;												 
	float enemy_collisionBOX_x;								 
	float enemy_collisionBOX_y;								
	float enemy_collisionBOX_w;										 
	float enemy_collisionBOX_h;										 
	bool movement;
	bool alive;

};
class enemy2 {
public:
	const float enemy2SPEED = 0.07;
	const int enemy2Size = 32;
	float enemy2POS_x;
	float enemy2POS_y;
	float enemy2_collisionBOX_x;
	float enemy2_collisionBOX_y;
	float enemy2_collisionBOX_w;
	float enemy2_collisionBOX_h;
	bool movement;
	bool alive;
};
class bullet {
public:
	bullet() {};
	const float BulletSpeed = 0.07;
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
	srand(time(NULL));
	bool gameover;	
	bool gameClose = false;

	const float playerSPEED = 0.04;					
	float playerPOS_x = 10;												  
	float playerPOS_y = 10;												  
	float player_collisionBOX_x = playerPOS_x;							  
	float player_collisionBOX_y = playerPOS_y;							  
	float player_collisionBOX_w = 0;										  
	float player_collisionBOX_h = 0;	
	int playerSize = 32;
	bool playerUp = true;
	bool playerDown = false;
	bool playerLeft = false;
	bool playerRight = false;
	
	int cantEnemys1 = 0;
	int cantEnemys2 = 0;
	int vidas = 3;
	int damageTimer = 0;
	bool BoolBullets = false;
	bool startScreen = true;
	bool endScreen = false;
	const int ScreenX = 640;
	const int ScreenY = 500;
	const float FPS = 60;
	int randX = 0;
	int randY = 0;
	bool arrayKeys[4] = { false,false,false,false };		
	int puntaje = 0;
	
	enemy* bicho1[10];
	enemy2* bicho2[10];

	bullet* bala = NULL; 
	
	ALLEGRO_DISPLAY *display = NULL;				
	ALLEGRO_BITMAP  *image = NULL;					
	ALLEGRO_BITMAP  *image2 = NULL;			
	ALLEGRO_BITMAP  *image3 = NULL;
	ALLEGRO_BITMAP  *image4 = NULL;
	ALLEGRO_BITMAP  *fondo = NULL;
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

	
	
	display = al_create_display(ScreenX, ScreenY);
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

	image3 = al_load_bitmap("a.png");
	if (!image3) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load enemy!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		return 0;
	}

	image4 = al_load_bitmap("Enemy2.png");
	if (!image4) {
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

	fondo = al_load_bitmap("pantallaDeInicio.png");
	if (!fondo) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load bullet!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		return 0;
	}

	for (int i = 0; i < cantEnemys1; i++)
	{
		bicho1[i]->enemy_collisionBOX_h = 32;
		bicho1[i]->enemy_collisionBOX_w = 32;
	}
	
	for (int i = 0; i < cantEnemys2; i++)
	{
		bicho2[i]->enemy2_collisionBOX_h = 32;
		bicho2[i]->enemy2_collisionBOX_w = 32;
	}
	if (!al_install_keyboard())    
	{
		al_show_native_message_box(display, "Error", "Error", "Failed to load keyboard!",NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 0;
	}


	al_install_audio();
	al_init_acodec_addon();
	ALLEGRO_SAMPLE *backgrounMusic = al_load_sample("Music.wav");
	ALLEGRO_SAMPLE *shootSound = al_load_sample("Shoot.wav");
	ALLEGRO_SAMPLE *damageSound = al_load_sample("Damage.wav");
	ALLEGRO_SAMPLE *lifeDownSound = al_load_sample("LifeDown.wav");



	al_reserve_samples(4);
	al_play_sample(backgrounMusic, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0);

	ALLEGRO_TIMER *timer = NULL;

	ALLEGRO_EVENT_QUEUE* event_queque = al_create_event_queue();
	ALLEGRO_EVENT events;
	al_register_event_source(event_queque, al_get_keyboard_event_source());

	timer = al_create_timer(1.0 / FPS);
	if (!timer)
	{
		al_show_native_message_box(display, "Error", "Error", "Failed to create timer", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	al_register_event_source(event_queque, al_get_timer_event_source(timer));
	al_start_timer(timer);


	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_FONT *font = al_load_ttf_font("arial.ttf", 24, 0);
	ALLEGRO_FONT *font2 = al_load_ttf_font("arial.ttf", 64, 0);


	if (!font) {
		fprintf(stderr, "Could not load 'arial.ttf'.\n");
		return -1;
	}

	if (!font2) {
		fprintf(stderr, "Could not load 'arial.ttf'.\n");
		return -1;
	}

	
	while (!gameClose)
	{

		gameover = false;

		int enemys1ToGenerate = ((rand() % 10) + 1);
		int enemys2ToGenerate = ((rand() % 10) + 1);


		for (int i = 0; i < enemys1ToGenerate; i++)
		{
			bicho1[i] = new enemy();
			randX = (rand() % ScreenX - 40);
			randY = (rand() % (ScreenY - 100));
			bicho1[i]->enemyPOS_x = randX;
			bicho1[i]->enemyPOS_y = randY + 40;
			bicho1[i]->enemy_collisionBOX_x = bicho1[i]->enemyPOS_x;
			bicho1[i]->enemy_collisionBOX_y = bicho1[i]->enemyPOS_y;
			bicho1[i]->enemy_collisionBOX_h = 0;
			bicho1[i]->enemy_collisionBOX_w = 0;
			bicho1[i]->movement = true;
			cantEnemys1++;
			bicho1[i]->alive = true;
		}

		for (int i = 0; i < enemys2ToGenerate; i++)
		{
			bicho2[i] = new enemy2();
			randX = (rand() % (ScreenX - 40));
			randY = (rand() % (ScreenY - 100));
			bicho2[i]->enemy2POS_x = randX + 60;
			bicho2[i]->enemy2POS_y = randY;
			bicho2[i]->enemy2_collisionBOX_x = bicho2[i]->enemy2POS_x;
			bicho2[i]->enemy2_collisionBOX_y = bicho2[i]->enemy2POS_y;
			bicho2[i]->enemy2_collisionBOX_h = 0;
			bicho2[i]->enemy2_collisionBOX_w = 0;
			bicho2[i]->movement = true;
			cantEnemys2++;
			bicho2[i]->alive = true;

		}

		bala = new bullet();
		bala->BulletPOS_x = playerPOS_x + (playerSize / 2);
		bala->BulletPOS_y = playerPOS_y + (playerSize / 2);
		bala->Bullet_collisionBOX_x = bala->BulletPOS_x;
		bala->Bullet_collisionBOX_y = bala->BulletPOS_y;
		bala->Bullet_collisionBOX_h = al_get_bitmap_height(bulletImage);
		bala->Bullet_collisionBOX_w = al_get_bitmap_width(bulletImage);



		while (!gameover)
		{
			al_get_next_event(event_queque, &events);

			if (startScreen == false && endScreen == false)
			{
				
				if (BoolBullets == false)
				{
					bala->BulletPOS_x = playerPOS_x + (playerSize / 2);
					bala->BulletPOS_y = playerPOS_y + (playerSize / 2);
				}

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
						gameClose = true;

						break;
					case ALLEGRO_KEY_SPACE:
						if (BoolBullets == false)
						{
							BoolBullets = true;
							bala->bulletUp = playerUp;
							bala->bulletDown = playerDown;
							bala->bulletLeft = playerLeft;
							bala->bulletRight = playerRight;
							al_play_sample(shootSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

						}
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

				if (playerPOS_x < 0)
				{
					playerPOS_x = 0;
				}
				if ((playerPOS_x + playerSize) > ScreenX)
				{
					playerPOS_x = ScreenX - playerSize;
				}

				if (playerPOS_y < 0)
				{
					playerPOS_y = 0;
				}
				if ((playerPOS_y + playerSize) > ScreenY)
				{
					playerPOS_y = ScreenY - playerSize;
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


				if (bala->BulletPOS_x > ScreenX || bala->BulletPOS_x < 0 || bala->BulletPOS_y > ScreenY || bala->BulletPOS_y < 0)
				{
					BoolBullets = false;
				}




				for (int i = 0; i < cantEnemys1; i++)
				{
					if (bicho1[i] != NULL)
					{
						if (bicho1[i]->enemyPOS_x >= ScreenX - bicho1[i]->enemySize)
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
					}
				}

				for (int i = 0; i < cantEnemys2; i++)
				{
					if (bicho2[i] != NULL)
					{
						if (bicho2[i]->enemy2POS_y >= ScreenY - bicho2[i]->enemy2Size)
						{
							bicho2[i]->movement = false;
						}
						if (bicho2[i]->enemy2POS_y <= 0)
						{
							bicho2[i]->movement = true;
						}
						if (bicho2[i]->movement == true)
						{
							bicho2[i]->enemy2POS_y += bicho2[i]->enemy2SPEED;
						}
						if (bicho2[i]->movement == false)
						{
							bicho2[i]->enemy2POS_y -= bicho2[i]->enemy2SPEED;
						}
					}
				}

			
				playerPOS_x += arrayKeys[RIGHT] * playerSPEED;
				playerPOS_x -= arrayKeys[LEFT] * playerSPEED;
				playerPOS_y += arrayKeys[DOWN] * playerSPEED;
				playerPOS_y -= arrayKeys[UP] * playerSPEED;

				player_collisionBOX_x = player_collisionBOX_w / 2;
				player_collisionBOX_y = player_collisionBOX_h / 2;
				for (int i = 0; i < cantEnemys1; i++)
				{
					if (bicho1[i] != NULL)
					{
						if ((playerPOS_x + playerSize >= bicho1[i]->enemyPOS_x && playerPOS_x <= bicho1[i]->enemyPOS_x + bicho1[i]->enemySize) && (playerPOS_y + playerSize >= bicho1[i]->enemyPOS_y && playerPOS_y <= bicho1[i]->enemyPOS_y + bicho1[i]->enemySize))
						{
							vidas--;
							al_play_sample(lifeDownSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

							playerPOS_x = 10;
							playerPOS_y = 10;
						}
						if (BoolBullets == true && ((bala->BulletPOS_x + bala->BulletSize >= bicho1[i]->enemyPOS_x && bala->BulletPOS_x <= bicho1[i]->enemyPOS_x + bicho1[i]->enemySize) && (bala->BulletPOS_y + bala->BulletSize >= bicho1[i]->enemyPOS_y && bala->BulletPOS_y <= bicho1[i]->enemyPOS_y + bicho1[i]->enemySize)))
						{
							bicho1[i]->alive = false;
							delete bicho1[i];
							bicho1[i] = NULL;///////////////////////////////////////
							BoolBullets = false;
							enemys1ToGenerate--;
							al_play_sample(damageSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
							puntaje += 10;

						}
					}
				}

				for (int i = 0; i < cantEnemys2; i++)
				{
					if (bicho2[i] != NULL)
					{
						if ((playerPOS_x + playerSize >= bicho2[i]->enemy2POS_x && playerPOS_x <= bicho2[i]->enemy2POS_x + bicho2[i]->enemy2Size) && (playerPOS_y + playerSize >= bicho2[i]->enemy2POS_y && playerPOS_y <= bicho2[i]->enemy2POS_y + bicho2[i]->enemy2Size))
						{
							vidas--;
							al_play_sample(lifeDownSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

							playerPOS_x = 10;
							playerPOS_y = 10;

						}
						if (BoolBullets == true && ((bala->BulletPOS_x + bala->BulletSize >= bicho2[i]->enemy2POS_x && bala->BulletPOS_x <= bicho2[i]->enemy2POS_x + bicho2[i]->enemy2Size) && (bala->BulletPOS_y + bala->BulletSize >= bicho2[i]->enemy2POS_y && bala->BulletPOS_y <= bicho2[i]->enemy2POS_y + bicho2[i]->enemy2Size)))
						{
							bicho2[i]->alive = false;




							BoolBullets = false;

							enemys2ToGenerate--;

							delete bicho2[i];





							bicho2[i] = NULL;
							al_play_sample(damageSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);


							puntaje += 10;




						}
					}
				}
				if (vidas <= 0)
				{					
					endScreen = true;
				}

				

				for (int i = 0; i < cantEnemys1; i++)
				{
					if (bicho1[i] != NULL)
					{
						al_draw_bitmap(image2, bicho1[i]->enemyPOS_x, bicho1[i]->enemyPOS_y, 0);
					}
				}
				for (int i = 0; i < cantEnemys2; i++)
				{
					if (bicho2[i] != NULL)
					{
						al_draw_bitmap(image4, bicho2[i]->enemy2POS_x, bicho2[i]->enemy2POS_y, 0);
					}
				}
				al_draw_bitmap(image3, 0, 0, 0);
				al_draw_bitmap(bulletImage, bala->BulletPOS_x, bala->BulletPOS_y, 0);
				al_draw_bitmap(image, playerPOS_x, playerPOS_y, 0);
				al_draw_textf(font, al_map_rgb(255, 255, 255), 10, ScreenY - 40, ALLEGRO_ALIGN_LEFT, "Puntaje: %i", puntaje);
				al_draw_textf(font, al_map_rgb(255, 255, 255), ScreenX - 10, ScreenY - 40, ALLEGRO_ALIGN_RIGHT, "Vidas: %i", vidas);

				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));


				if (enemys1ToGenerate == 0 && enemys2ToGenerate == 0)
				{
					cantEnemys1 = 0;
					cantEnemys2 = 0;

					playerPOS_x = 10;
					playerPOS_y = 10;
					gameover = true;
				}
			}

			if (startScreen == true && endScreen == false)
			{
				al_draw_bitmap(fondo, 0, 0, 0);
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));

				if (events.type == ALLEGRO_EVENT_KEY_DOWN)
				{
					switch (events.keyboard.keycode)
					{
					case ALLEGRO_KEY_A:
						startScreen = false;

						break;

					case ALLEGRO_KEY_ESCAPE:
						gameover = true;
						gameClose = true;
						break;
					}
				}

			}

			if (startScreen == false && endScreen == true)
			{
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));

				al_draw_text(font2, al_map_rgb(255, 255, 255), ScreenX/2, ScreenY/2 - 80, ALLEGRO_ALIGN_CENTRE, "GAMEOVER");
				al_draw_textf(font2, al_map_rgb(255, 255, 255), ScreenX / 2, ScreenY / 2 , ALLEGRO_ALIGN_CENTRE, "Puntaje: %i", puntaje);
				al_draw_text(font, al_map_rgb(255, 255, 255), 10, ScreenY - 40, ALLEGRO_ALIGN_LEFT, "Pulsa Esc para salir");
				

				if (events.type == ALLEGRO_EVENT_KEY_DOWN)
				{
					switch (events.keyboard.keycode)
					{	
					case ALLEGRO_KEY_ESCAPE:
						gameover = true;
						gameClose = true;				
						break;
					}
				}

			}

			


		}
	}
	al_destroy_display(display);
	al_destroy_bitmap(fondo);
	al_destroy_bitmap(bulletImage);
	al_destroy_bitmap(image4);
	al_destroy_bitmap(image3);
	al_destroy_bitmap(image2);
	al_destroy_bitmap(image);
	al_destroy_sample(backgrounMusic);
	al_destroy_sample(shootSound);
	al_destroy_sample(damageSound);
	al_destroy_sample(lifeDownSound);	
	al_destroy_font(font);
	al_destroy_font(font2);

	al_destroy_event_queue(event_queque);

	
	for (int i = 0; i < cantEnemys1; i++)
	{
		if (bicho1[i] != NULL)
		{
			delete bicho1[i];
		}
	}
	for (int i = 0; i < cantEnemys2; i++)
	{
		if (bicho2[i] != NULL)
		{
			delete bicho2[i];
		}
	}

	delete bala;

	return 0;
}

