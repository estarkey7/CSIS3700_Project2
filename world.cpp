#include "world.h"
#include <cassert>
#include <algorithm>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_primitives.h"
#include "sprite.h"

#include "player_sprite.h"
#include "obstruction_sprite.h"
#include "collision.h"
#include "image_library.h"
#include "coin.h"

using namespace std;

namespace csis3700 {

  const float gravity_acceleration = 600;

  void free_sprite(sprite* s) {
	delete s;
  } 

  world::world(size_t width_in, size_t height_in, ALLEGRO_DISPLAY *display) {
	  gameDisplay = display;
	  DISPLAY_SIZE.Set(width_in, height_in);

		// INITIALIZE CAMERA
	  camera.Set(DISPLAY_SIZE.get_x() / 2, DISPLAY_SIZE.get_y() / 2);
		
		cout << sprite_id_count;

		// SETUP AUDIO SAMPLES
		game_music = al_load_sample("game_music.wav");
		jump_sound = al_load_sample("jump.wav");
		player_change_direction_sound = al_load_sample("player_change_direction.wav");
		player_landing_sound = al_load_sample("player_landing.wav");
		walk_sound = al_load_sample("alien_walk.wav");

		// SETUP AUDIO SAMPLE INSTANCES
		jump_sound_instance = al_create_sample_instance(jump_sound);
		player_landing_sound_instance = al_create_sample_instance(player_landing_sound);
		player_change_direction_sound_instance = al_create_sample_instance(player_change_direction_sound);
		walk_sound_instance = al_create_sample_instance(walk_sound);
		
		// ATTACH AUDIO SAMPLE INSTANCES TO MIXER
		al_attach_sample_instance_to_mixer(jump_sound_instance, al_get_default_mixer());
		al_attach_sample_instance_to_mixer(player_landing_sound_instance, al_get_default_mixer());
		al_attach_sample_instance_to_mixer(player_change_direction_sound_instance, al_get_default_mixer());
		al_attach_sample_instance_to_mixer(walk_sound_instance, al_get_default_mixer());

		// START GAME_MUSIC
		al_play_sample(game_music, .4f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_LOOP, &id);
		
		
		
		
		

		// CREATE PLAYER OBJECT AS THE FIRST OBJECT
		player = new player_sprite("player", (DISPLAY_SIZE.get_x() / 2.0f) - 300, (DISPLAY_SIZE.get_y() / 2) + 100, 1, 1, image_library::get_instance()->get("player_idle1.png"), 50.0f, 250.0f, 325.1f, &camera, player_landing_sound_instance, player_change_direction_sound_instance, walk_sound_instance);
				
	
			make_ground(level);
		
		

		
			
		//obstruction_sprite *magic_balloon2 = new obstruction_sprite("magic_balloon", 0, 500, .2f, .2f, image_library::get_instance()->get("balloon1.png"));
		//magic_balloon2->set_image_sequence(balloon_sequence);
		//sprites.push_back(magic_balloon2);
		
		//sprites.push_back(new coin("coin", 400.0f, (float)(DISPLAY_SIZE.get_y() - 500), 1.0f, 1.0f, image_library::get_instance()->get("coin1.png"), 0.0f, 20));
		

	srand((unsigned int)clock() * 3305193169);

	

	  sprites.push_back(player);
	
	  Key_Input.get_instance();
	
  
  }

  void world::destroy_level()
  {
	  for (int i = 0; i < enemySpawnLocationQueue.size(); i++)
		  enemySpawnLocationQueue.pop();

	 for (vector<sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it)
	  {
		  string name = (*it)->get_name();

		  if (name == "ground") { (*it)->set_visible(false); }
		  else if (name == "balloon") { (*it)->set_visible(false); }
		  else if (name == "winning_platform") { (*it)->set_visible(false); }
		  else if (name == "enemy") { (*it)->set_visible(false); }
		  else if (name == "coin") { (*it)->set_visible(false); }
		  else if (name == "magic_balloon") { (*it)->set_visible(false); }
		  else if (name == "solid_balloon") { (*it)->set_visible(false); }
		  

		 
	  }
	  cout << "****** LEVEL " << level << " destroyed ******" << endl;
	  
  }
  void world::make_ground(int level_in){
	  if (player->reload_level == false){ return; }

	  if (level_in == 1)
	  {
		  // INITIAL SPLASH SCREEN
		  build_background(-4021, -20, 15);

		  // LEVEL ONE

		  // LOAD ENEMY SPAWNS
		  addEnemeySpawnVectors();
			// MAIN GROUND
				// Secret Bonus Platform way to the left of respawn point
				  build_platform(-3319, -200, 2);
				  build_platform(-3450, -140, 1, 3);
				  build_platform(-3450, 300, 1, 2);
				  simple_balloon(-3450, DISPLAY_SIZE.get_y()- 650);
				  
				  build_platform(-3450, 1100, 2, 1);

		  build_platform(5000, 20, 1, 1, "ground", "ground_5000.png", 5000, 50);
		  for (int i = 10500; i < 18000; i += 2000)
			  build_platform(i, 20, 1, 1, "ground", "ground_2000.png", 3200, 50);

		  // START AT LOCATION (0, 0). MAKE 8x1 BLOCK PLATFORM (50x50 per block). Default parameters are for ground objects
		  // (0,0) -> (750,0) : 8x1 

		  build_platform(0, 0, 3, 1, "ground", "ground_300.png", 300, 50);

		  // (1750,0) -> (2950,0) : 40x1 
		  build_platform(1750, 0, 4, 1, "ground", "ground_300.png", 300, 50);
		  build_platform(1950, -200, 1, 1, "ground", "ground_300.png", 300, 50);

		  // (3000,0) -> (3400,0) : 8x1 
		  build_platform(4300, 0, 1, 1, "ground", "ground_300.png", 300, 50);


		  // FIRST PLATFORM
		  build_platform(0, 500, 1, 1, "winning_platform", "ground_300.png", 300, 50);

		  // SECOND PLATFORM
		  build_platform(3300, 300, 1, 1, "ground", "ground_300.png", 300, 50);


		  // END RISING PLATFORMS
		  build_platform(12546, 200, 1, 1, "ground", "ground_300.png", 300, 50);
		  build_platform(12926, 400, 1, 1, "ground", "ground_300.png", 300, 50);
		  simple_balloon(13882, 200, true);
		  build_platform(14127, 700, 1, 1, "ground", "ground_300.png", 300, 50);
		  build_platform(14924, 900, 1, 1, "ground", "ground_300.png", 300, 50);
		  simple_balloon(15882, -400, true);
		  simple_balloon(16782, -600, true);
		  build_platform(17027, 1200, 3, 3, "winning_platform", "ground_300.png", 300, 50);

		  // COINS sprites.push_back(new coin("coin", 400.0f, (float)(DISPLAY_SIZE.get_y() - 500), 1.0f, 1.0f, image_library::get_instance()->get("coin1.png"), 0.0f, 20));
		  /*
		  sprites.push_back(new coin("coin", 400.0f, (float)(DISPLAY_SIZE.get_y() - 500), 1.0f, 1.0f, image_library::get_instance()->get("coin1.png"), 0.0f, 20));
		  
		  for (int i = 0; i < 1000; i += 200)
		  {
			  sprites.push_back(new coin("coin", 2200.0f + i, (float)(DISPLAY_SIZE.get_y() - 500), 1.0f, 1.0f, image_library::get_instance()->get("coin1.png"), 0.0f, 20));
		  }
		  
		  sprites.push_back(new coin("coin", 2000.0f, 853, 1.0f, 1.0f, image_library::get_instance()->get("coin1.png"), 0.0f, 20));
		  sprites.push_back(new coin("coin", 4000.0f, (float)(DISPLAY_SIZE.get_y() - 500), 1.0f, 1.0f, image_library::get_instance()->get("coin1.png"), 0.0f, 20));
		  */
	  
		  sprites.push_back(new balloon("balloon", 600.0f, (float)(DISPLAY_SIZE.get_y() - 400), .2f, .2f, image_library::get_instance()->get("coin1.png"), 0.0f, 20));
		  simple_balloon(5016.0f, 440);
		  simple_balloon(2829, 1049);
		  simple_balloon(3300, DISPLAY_SIZE.get_y() - 500);
		  simple_balloon(-3450, -500, false, true);
		  simple_balloon(-800, 700, true);
 
		  
	  }
	  else if (level_in == 2)
	  {

		  addEnemeySpawnVectors();
		  // THE GAUNTLET LEVEL

		  // STARTING PLATFORM
		  build_platform(0, 0, 1, 1, "ground", "ground_5000.png", 5000, 50);
		  build_platform(0, 300, 6, 1, "ground", "ground_300.png", 800, 50);
		  simple_balloon(2500, 400, false, true);
		  
	  }
	  createCoins();
	  // TINY DIRT RESPAWN PLATFORM
	  sprites.push_back(new obstruction_sprite("ground", 358, DISPLAY_SIZE.get_y() - 200, .5f, .1f, image_library::get_instance()->get("ground dirt.png")));
	  
	  player->reload_level = false;
	  player->winning_tint = 0.0f;
  }

  void world::simple_balloon(float x, float y, bool is_solid, bool is_magical )
  {
	  if (is_magical == false)
	  {
		  if (is_solid == false)
			  sprites.push_back(new balloon("balloon", x, y, .2f, .2f, image_library::get_instance()->get("coin1.png"), 0.0f, 20));
		  else
		  {
			  sprites.push_back(new balloon("solid_balloon", x, y, .2f, .2f, image_library::get_instance()->get("coin1.png"), 0.0f, 20));
		  }
	  }
	  else
	  {
		  sprites.push_back(new balloon("magic_balloon", x, y, .2f, .2f, image_library::get_instance()->get("coin1.png"), 0.0f, 20));
	  }
  }

  void world::addEnemeySpawnVectors()
  {
	 
	  if (level == 1)
	  {
		  switch (difficultyLevel)
		  {
		  case EASY:
			  enemySpawnLocationQueue.push(Vector2(1750, 0));
			  enemySpawnLocationQueue.push(Vector2(3200, 0));
			  enemySpawnLocationQueue.push(Vector2(4700, 0));
			  enemySpawnLocationQueue.push(Vector2(5400, 0));
			  enemySpawnLocationQueue.push(Vector2(7700, 0));
			  break;

		  case HARD:
			  enemySpawnLocationQueue.push(Vector2(1750, 0));
			  enemySpawnLocationQueue.push(Vector2(2050, 0));
			  enemySpawnLocationQueue.push(Vector2(2250, 0));
			  enemySpawnLocationQueue.push(Vector2(3200, 0));
			  enemySpawnLocationQueue.push(Vector2(3600, 0));
			  enemySpawnLocationQueue.push(Vector2(4700, 0));
			  enemySpawnLocationQueue.push(Vector2(5400, 0));
			  enemySpawnLocationQueue.push(Vector2(7700, 0));
			  enemySpawnLocationQueue.push(Vector2(14000, 0));
			  enemySpawnLocationQueue.push(Vector2(15000, 0));
			  enemySpawnLocationQueue.push(Vector2(16000, 0));
			  enemySpawnLocationQueue.push(Vector2(18000, 0));
			  break;


		  }
	  }
	  else
	  {
		  switch (difficultyLevel)
		  {
		  case EASY:
			  enemySpawnLocationQueue.push(Vector2(700, 0));
			  enemySpawnLocationQueue.push(Vector2(1200, 0));
			  enemySpawnLocationQueue.push(Vector2(1800, 0));
			  enemySpawnLocationQueue.push(Vector2(2500, 0));
			  enemySpawnLocationQueue.push(Vector2(4200, 0));
			  break;

		  case HARD:
			  enemySpawnLocationQueue.push(Vector2(700, 0));
			  enemySpawnLocationQueue.push(Vector2(100, 0));
			  enemySpawnLocationQueue.push(Vector2(1550, 0));
			  enemySpawnLocationQueue.push(Vector2(1800, 0));
			  enemySpawnLocationQueue.push(Vector2(2200, 0));
			  enemySpawnLocationQueue.push(Vector2(2500, 0));
			  enemySpawnLocationQueue.push(Vector2(3000, 0));
			  enemySpawnLocationQueue.push(Vector2(3500, 0));
			  enemySpawnLocationQueue.push(Vector2(4000, 0));
			  enemySpawnLocationQueue.push(Vector2(4200, 0));
			  enemySpawnLocationQueue.push(Vector2(4700, 0));
			  enemySpawnLocationQueue.push(Vector2(4900, 0));
			  break;


		  }
	  }

	  
  }

  void world::build_platform(int init_x, int init_y, int x_scale, int y_scale, string object_name_in, string object_location_string_in,int object_width_in, int object_height_in){
	  /*
		PLATFORM CREATOR
			- More easily create platform loops to build maps
			- It initializes obstruction_sprites as the objects
			(NOTE* I SET THE obstruction_sprites initial_y parameter = (768 -y),
				so it's referrencing the objects location from the (0, 768) origin,
				or "bottom-left corner" (not the default "top-left corner")

				This should make the ground location have a y-parameter of 0.

		How to use:
			- call function in world constructor above with the following parameters(in order):
				- starting x location of platform (int init_x)
				- starting y location of platform (int init_y). *** starting from 0, not 768! (See Note above if confused)
				- length of platform in terms of repeating the objects width, x_scale times. (so a 50 px wide object with a (x_scale == 3) will create a 150 px long platform)
				- height of platform in terms of repeating the objects height, 'y_scale' times. (int y_scale)
				- name of object. used as an identity in collisions. (string  object_name_in)
				- file name of object within the "Images" folder. (string object_location_string_in).
				- width of objects image file. ( int object_width_in)
				- height of objects image file. ( int object_height_in)

			EXAMPLE: MAKE A WOOD TEXTURE PLATFORM AT LOCATION (0, 200) that's 10 textures long.
						(assume wood.png is 60px wide and 30px tall)

				build_platform(0, 200, 10, 1, "platform", "wood.png", 60, 30);

	  */
		
	  for (int x = init_x; x < (init_x + (x_scale * object_width_in)); x += object_width_in){
		  for (int y = init_y; y < init_y + (y_scale * object_height_in) ; y += object_height_in){
			  sprites.push_back(new obstruction_sprite(object_name_in, x, DISPLAY_SIZE.get_y() - y - object_height_in, 1.0f, 1.0f, image_library::get_instance()->get(object_location_string_in)));
		  }
	  }

  }

  void world::build_background(int init_x, int init_y, int width ){
	  obstruction_sprite *splash = new obstruction_sprite("splash", -200, -20, 1.0f, 1.0f, image_library::get_instance()->get("woods_splash2.png")); // y should be 330 for 1920x1080 res
	  obstruction_sprite *splash2 = new obstruction_sprite("splash", -3959, -881, 1.0f, 1.0f, image_library::get_instance()->get("splash.png")); // y should be 330 for 1920x1080 res
	  for (int x = init_x; x < (init_x + (width * 1081)); x += 1081){
		   
		  sprites.push_back(new obstruction_sprite("background", x, init_y, 1.0f, 1.0f, image_library::get_instance()->get("woods_green.png")));
		  
	  }
	  
	  sprites.push_back(splash);
	  sprites.push_back(splash2);

  }

  void world::fade(){
	  // DOES NOT WORK
	  for (float alpha = 1.0; alpha > 0.0; alpha -= 0.1)
	  {
		  al_draw_filled_rectangle(55, 55, 60, 60, al_map_rgb(255, 0, 0));
		  al_draw_filled_rectangle(50, 50, 100, 100, al_map_rgba_f(1 * alpha, 1 * alpha, 1 * alpha, alpha));
		  al_flip_display();
		  al_clear_to_color(al_map_rgb(0, 0, 0));
		  al_rest(0.1);
	  }
  }

  world::world(const world& other) {
	assert(false); // do not copy worlds
  }

 // world& world::operator=(const world& other) {
 //   assert(false); // do not assign worlds
	//return world;
 // }

  world::~world() {
	for_each(sprites.begin(), sprites.end(), free_sprite);
	sprites.clear();
	//Remove sounds.
	al_destroy_sample_instance(jump_sound_instance);
	al_destroy_sample(game_music);
	al_destroy_sample(player_change_direction_sound);
	al_destroy_sample(jump_sound); 
	
  }

  void world::handle_event(ALLEGRO_EVENT ev) {
	if(ev.type == ALLEGRO_EVENT_KEY_DOWN && can_move) {
		

		switch (ev.keyboard.keycode){
				//case ALLEGRO_KEY_A :  player->move(MOVE_LEFT); break;
								 
				case ALLEGRO_KEY_S:   player->move(HOVER);
					
					break;
								 
				//case ALLEGRO_KEY_D :  player->move(MOVE_RIGHT); break;
								 
				//case ALLEGRO_KEY_W:  player->move(JUMP); break;			  
								 
				case ALLEGRO_KEY_LEFT : player->move(MOVE_LEFT);
					
					break;
								 
				case ALLEGRO_KEY_RIGHT :  player->move(MOVE_RIGHT);
					
					break;
				
				case ALLEGRO_KEY_UP :  player->move(JUMP, jump_sound_instance);
					
					break;
				
				case ALLEGRO_KEY_DOWN:  player->move(HOVER); 
					
					break;

				case ALLEGRO_KEY_H:  player->remove_health(10); break;
				
				case ALLEGRO_KEY_SPACE :  
					for (vector<sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it){

						if ((*it)->get_name() == "enemy"){
							(*it)->print_initial_configuration();
						}

					}
					for (vector<sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it){

						if ((*it)->get_name() == "player"){
							(*it)->print_initial_configuration();
						}
						
					}
					cout << "Objects in world: " << sprites.size() << endl;
						break;
				case ALLEGRO_KEY_P:
					al_stop_sample(&id);
					al_show_native_message_box(
						gameDisplay,
						"Game Paused",
						"",
						"Press OK to unpause game.",
						NULL,
						ALLEGRO_MESSAGEBOX_WARN
						);
					al_play_sample(game_music, .4f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_LOOP, &id);

					break;
				case ALLEGRO_KEY_ESCAPE :
					int button = 0;
					button = al_show_native_message_box(
						gameDisplay,
						"Close Project II",
						"",
						"You are about to exit the game, is that okay?",
						NULL,
						ALLEGRO_MESSAGEBOX_YES_NO
						);

						if(button == 1)
						{
							std::exit(0);
						}
						
					break;
				
										
		}
	}
  
  }

  void world::resolve_collisions() {
	std::vector<collision> collisions;
	
	for(int i = 0; i < sprites.size(); i++){
	
		for(int j = 0; j < i; j++){
			if(sprites[i]->collides_with(*sprites[j])){
			// add to collisions
				collisions.push_back( collision(sprites[i], sprites[j]) );
			}
		
		}
	
	}
	
	
	for(int i = 0; i < collisions.size(); i++){
		if(collisions[i].is_active()){
			collisions[i].resolve();
		}
	}
  }

  void world::advance_by_time(double dt) {
	  if (can_move)
	  {
		  if (Key_Input.get_instance()->is_key_down(ALLEGRO_KEY_W)){
			  //cout << "KEY_DOWN: W................" << endl;
			  player->move(JUMP, jump_sound_instance);

		  }
		  /*
			  else if (Key_Input.get_instance()->is_key_down(ALLEGRO_KEY_S)){
			  cout << "KEY_DOWN: S................" << endl;
			  player->move(HOVER);
			  }
			  */

		  if (Key_Input.get_instance()->is_key_down(ALLEGRO_KEY_A)){
			  //cout << "KEY_DOWN: A" << endl;
			  player->move(MOVE_LEFT, player_change_direction_sound_instance);
		  }
		  else if (Key_Input.get_instance()->is_key_down(ALLEGRO_KEY_D)){
			  //cout << "KEY_DOWN: D................" << endl;
			  player->move(MOVE_RIGHT, player_change_direction_sound_instance);
		  }
	  }
	 
	  sprite* deletable_sprite = NULL;

	  for (vector<sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it)
	  {
		  (*it)->advance_by_time(dt);
		  if (deletable_sprite == NULL && (*it)->get_visible() == false  )
		  {
			  deletable_sprite = (*it);
			  
		  }

	  }

	  if (deletable_sprite != NULL)
	  {
		  //cout << endl <<"DELETING OBJECT: " << (deletable_sprite)->get_name() << " (ID: " << (deletable_sprite)->get_sprite_id() << " )" << endl;
		  if (deletable_sprite->get_name() == "coin")
			  coin_count--;

		  sprites.resize(std::remove(sprites.begin(), sprites.end(), deletable_sprite) - sprites.begin());
		  //cout << "OBJECT DELETED" << endl << endl;
		  delete deletable_sprite;
	  }
	  else if ( player->player_has_won && player->current_level == 1 && player->reload_level == true)
	  {
		  // IF PLAYER BEATS LEVEL ONE AND ITS FADE SCREEN IS OVER
		  destroy_level();
		  player->current_level = 2;
		  level = 2;
		  player->player_has_won = false;
	  }
	  else
	  {
		  // EVERYTHING IS DELETED AND LEVEL NEEDS LOADED
		  make_ground(level);
	  }

	   
	  
	  
	  

	  if (player->player_has_won)
		  al_stop_sample(&id);

	  
		  
	  
	  //(*it)->set_velocity;
	resolve_collisions();

	static double timeFlag = 0;
	
	if (timeFlag > .7 && messageBoxAlreadyShown == false)
	{
		int button = 0;
		button = al_show_native_message_box(
			gameDisplay,
			"Select Game Difficulty",
			"",
			"Do you want to play this game on higher difficulty?",
			NULL,
			ALLEGRO_MESSAGEBOX_YES_NO
			);

		if (button == 1)
		{
			difficultyLevel = HARD;
			messageBoxAlreadyShown = true;
		}
		else
		{
			difficultyLevel = EASY;
			messageBoxAlreadyShown = true;
		}	

	}
	timeFlag += dt;
	
	checkForEnemySpawn();
	if (player->current_level == 2 && level == 2 && player->reload_level == false && coin_count <= 0)
	{
		player->game_over = true;
			
		
		player->player_has_won == true;

	}
  }

  void world::draw() {

	  if (camera.x < 12000){
		  if (camera.y > 0)
		  {
			  al_clear_to_color(al_map_rgb(0, 0, 0));
		  }
		  else
		  {
			  int color_amount = (0 + (-camera.y * 0.1));
			  al_clear_to_color(al_map_rgb(0, 0, color_amount));
		  }
	  }
	  else if (camera.x < 18000)
	  {
		  int color_amount = (255 - ((18000 - camera.x) * 0.0425));
		  al_clear_to_color(al_map_rgb(0, color_amount, 0));
	  }
	  else
	  {

		  al_clear_to_color(al_map_rgb(255, 0, 0));
	  }
	  
	  
	for(vector<sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it)
	  (*it)->draw(&camera);
	al_draw_rounded_rectangle       (20, 20, 200, 60, 15, 15, al_map_rgba( 0,  0,  0, 200), 7);
	al_draw_rounded_rectangle       (20, 20, 200, 60, 15, 15, al_map_rgba(15, 60, 15,  20), 4);
	al_draw_filled_rounded_rectangle(24, 24, 196, 56, 11, 11, al_map_rgba(15, 30, 15, 230));
	al_draw_textf(rapier24, al_map_rgba(15, 120, 15, 255), 35, 27, ALLEGRO_ALIGN_LEFT, "SCORE : %i", player->get_score());
	if (player->get_health() >= 50)
	al_draw_filled_rectangle(al_get_display_width(gameDisplay) - 200.0f, 25.0f, al_get_display_width(gameDisplay) - 200.0f + (player->get_health() * 1.5f), 40.0f, al_map_rgba(15, 200, 15, 200));
	else 
		al_draw_filled_rectangle(al_get_display_width(gameDisplay) - 200.0f, 25.0f, al_get_display_width(gameDisplay) - 200.0f + (player->get_health() * 1.5f), 40.0f, al_map_rgba(200, 15, 15, 200));
	
	al_draw_textf(rapier24, al_map_rgba(200, 200, 200, 225), al_get_display_width(gameDisplay) - 200.0f + (player->get_health() * 1.25f), 50, ALLEGRO_ALIGN_CENTER, "%i", player->get_health());
	al_draw_rectangle(al_get_display_width(gameDisplay) - 200.0f, 25.0f, al_get_display_width(gameDisplay) - 200.0f + (100 * 1.5f), 40.0f, al_map_rgba(15, 15, 200, 200),3);
	
	// PLAYER WINS GAME
	if (player->game_over)
	{
	
		if (game_winning_tint <= 255)
			{
				// FADE SPEED from 0 => 255
				game_winning_tint += 1.33;
			}

		
		al_draw_filled_circle((DISPLAY_SIZE.get_x() / 2), (DISPLAY_SIZE.get_y() / 2), 4 * (game_winning_tint), al_map_rgba(0, 0, 0, game_winning_tint));
		al_draw_textf(rapier48, al_map_rgba(15, 200, 15, 225), al_get_display_width(gameDisplay) / 2, al_get_display_height(gameDisplay) / 2, ALLEGRO_ALIGN_CENTRE, "YOU WIN!");
	}
  }


  void world::createEnemies()
  {
	  float right_edge = camera.get_x() + (al_get_display_width(gameDisplay) / 2);
	  float top_edge = camera.get_y() - (al_get_display_height(gameDisplay) / 2);

	  switch (difficultyLevel)
	  {
	  case EASY:
		  for (int x = 0; x < 5; x++)
		  {
			  enemy_sprite * enemy = new enemy_sprite("enemy", randomGenerator(right_edge + 100, right_edge + 600), top_edge - 20, 1, 1, NULL, randomGenerator(40, 60), randomGenerator(0, 1) ? true : false, (float)randomGenerator(60,70));
			  sprites.push_back(enemy);
			  enemies.push_back(enemy);
			  enemy_count++;
		  }
		  break;

	

	 

	  case HARD:
		  for (int x = 0; x < 7; x++)
		  {
			  enemy_sprite * enemy = new enemy_sprite("enemy", randomGenerator(right_edge, right_edge + 3000), randomGenerator(top_edge - 300,top_edge + 20), (float)randomGenerator(1, 2), (float)randomGenerator(1, 2), NULL, randomGenerator(40, 120), randomGenerator(0, 1) ? true : false, (float)randomGenerator(90, 400), 25, true, (&camera));
			  sprites.push_back(enemy);
			  enemies.push_back(enemy);
			  enemy_count++;
		  }
		  break;

	

	  }
  }

  void world::createCoins()
  {
	  if (level == 1)
	  {
		  for (int x = 0; x < 12000; x += randomGenerator(250, 500))
		  {
			  coin * newCoin;// = new coin("coin", x, 0, 1.0, 1.0, image_library::get_instance()->get("coin1.png"), 0.0, 20.0);
			  if (randomGenerator(1, 20) == 7)
			  {
				  newCoin = new coin("coin", x, 0, 2.0, 2.0, image_library::get_instance()->get("coin1.png"), 0.0, 20.0);
				  newCoin->set_image_sequence(newCoin->coinSpecialSequence);
				  newCoin->setMoveSpeed(35.0);
				  newCoin->set_score_value(150);
			  }
			  else
			  {
				  newCoin = new coin("coin", x, 0, 1.0, 1.0, image_library::get_instance()->get("coin1.png"), 0.0, 20.0);
			  }
			  sprites.push_back(newCoin);
			  coin_count++;
		  }
	  }
	  else
	  {
		  for (int x = 0; x < 5000; x += randomGenerator(100, 250))
		  {
			  coin * newCoin;// = new coin("coin", x, 0, 1.0, 1.0, image_library::get_instance()->get("coin1.png"), 0.0, 20.0);
			  if (randomGenerator(1, 20) == 7)
			  {
				  newCoin = new coin("coin", x, 0, 2.0, 2.0, image_library::get_instance()->get("coin1.png"), 0.0, 20.0);
				  newCoin->set_image_sequence(newCoin->coinSpecialSequence);
				  newCoin->setMoveSpeed(35.0);
				  newCoin->set_score_value(150);
			  }
			  else
			  {
				  newCoin = new coin("coin", x, 0, 1.0, 1.0, image_library::get_instance()->get("coin1.png"), 0.0, 20.0);
			  }
			  sprites.push_back(newCoin);
			  coin_count++;
		  }

	  }
  }

  void world::checkForEnemySpawn()
  {	  
	  if (enemySpawnLocationQueue.size() > 0)
	  {
		  if (camera.get_x() >= enemySpawnLocationQueue.front().get_x())
		  {
			  Vector2 tempVect = enemySpawnLocationQueue.front();
			  enemySpawnLocationQueue.pop();
			  createEnemies();
			  
		  }
	  }

	  
  }

  int world::randomGenerator(int min, int max)
  {
	  static int previous = 0;

	  while (1)
	  {
		  //Seed rnd number. This is not working correctly.

		  if (previous != rand() % (max - min + 1) + min)
		  {
			  previous = rand() % (max - min + 1) + min;
			  return rand() % (max - min + 1) + min;
			  break;
		  }
	  }
  }
  

}
