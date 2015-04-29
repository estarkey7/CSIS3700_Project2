#include "world.h"
#include <cassert>
#include <algorithm>
#include "sprite.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "player_sprite.h"
#include "obstruction_sprite.h"
#include "collision.h"
#include "image_library.h"

using namespace std;

namespace csis3700 {

  const float gravity_acceleration = 600;

  void free_sprite(sprite* s) {
	delete s;
  } 

  world::world() {
	  camera.Set(1024 / 2, 768 / 2);
	  view_rect.Set(1024, 768);
	  game_music = al_load_sample("game_music.wav");
	  jump_sound = al_load_sample("jump.wav");
	  player_change_direction_sound = al_load_sample("player_change_direction.wav");
	  player = new player_sprite("player", (1024.0f / 2.0f) - 300, (768.0f / 2) + 100, image_library::get_instance()->get("player_idle1.png"), 100.0f, 250.0f, 400.0f, &camera, jump_sound);
	  //al_play_sample(game_music, .4f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, NULL);  
	  obstruction_sprite *splash = new obstruction_sprite("splash", -200, -20 , image_library::get_instance()->get("woods_splash2.png"));
	  obstruction_sprite *ground = new obstruction_sprite("ground",(1024.0f /2.0f) - 20.0f, 768.0f - 50  ,image_library::get_instance()->get("ground.png"));
	  build_background(-1859, -20, 14);
	  sprites.push_back(splash);
	  make_ground();
	  
	  
	
	  //player->idle_sequence->add_image(image_library::get_instance()->get("player02.png"), .2);
	 
	
	  sprites.push_back(player);
	
	  Key_Input.get_instance();
	
  
  }

  void world::make_ground(){

	  // MAIN GROUND

	  // START AT LOCATION (0, 718). MAKE 8 BLOCKS (50x50 px each) times 1 ROW (50 pxs high)
	  build_platform(0, 0, 8, 1); 


	 // build_platform(0, 718, 8, 1);
	  for (int i = 0; i < 3000; i += 50){
			
		  if (i <= 400 || i > 800)
			  sprites.push_back(new obstruction_sprite("ground", i , 768.0f - 50, image_library::get_instance()->get("ground.png")));
	  }

	  // FIRST PLATFORM
	  for (int i = 550; i < 1024 - 300; i += 50){

		  sprites.push_back(new obstruction_sprite("ground", i, 768.0f - 250, image_library::get_instance()->get("ground.png")));
	  }

	  // SECOND PLATFORM
	  build_platform(1200, 260, 10, 1);
	  
	  
  }

  void world::build_platform(int init_x, int init_y, int x_scale, int y_scale,
							 string object_name_in, string object_location_string_in,
							 int object_width_in, int object_height_in){
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
			  sprites.push_back(new obstruction_sprite(object_name_in, x, 768 - y, image_library::get_instance()->get(object_location_string_in)));
		  }
	  }

  }

  void world::build_background(int init_x, int init_y, int width ){

	  for (int x = init_x; x < (init_x + (width * 1081)); x += 1081){
		   
		  sprites.push_back(new obstruction_sprite("background", x, init_y, image_library::get_instance()->get("woods_green.png")) );
		  
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
	al_destroy_sample(game_music);
	al_destroy_sample(player_change_direction_sound);
	al_destroy_sample(jump_sound); 
	
  }

  void world::handle_event(ALLEGRO_EVENT ev) {
	if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
		

		switch (ev.keyboard.keycode){
				//case ALLEGRO_KEY_A :  player->move(MOVE_LEFT); break;
								 
				case ALLEGRO_KEY_S:   player->move(HOVER); break;
								 
				//case ALLEGRO_KEY_D :  player->move(MOVE_RIGHT); break;
								 
				//case ALLEGRO_KEY_W:  player->move(JUMP); break;			  
								 
				case ALLEGRO_KEY_LEFT : player->move(MOVE_LEFT); break;
								 
				case ALLEGRO_KEY_RIGHT :  player->move(MOVE_RIGHT);break;
				
				case ALLEGRO_KEY_UP :  player->move(JUMP, jump_sound); break;
				
				case ALLEGRO_KEY_DOWN:  player->move(HOVER); break;
				
				case ALLEGRO_KEY_SPACE :  
					
					for (vector<sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it){

						if ((*it)->get_name() == "player"){
							(*it)->print_initial_configuration();
						}
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
	  if (Key_Input.get_instance()->is_key_down(ALLEGRO_KEY_W)){
		  cout << "KEY_DOWN: W................" << endl;
		  player->move(JUMP, jump_sound);

	  }
	  /*
		  else if (Key_Input.get_instance()->is_key_down(ALLEGRO_KEY_S)){
			  cout << "KEY_DOWN: S................" << endl;
			  player->move(HOVER);
		  }
	  */
	  
	  if (Key_Input.get_instance()->is_key_down(ALLEGRO_KEY_A)){
		  cout << "KEY_DOWN: A" << endl;
		  player->move(MOVE_LEFT, player_change_direction_sound);
	  }
	  else if (Key_Input.get_instance()->is_key_down(ALLEGRO_KEY_D)){
		  cout << "KEY_DOWN: D................" << endl;
		  player->move(MOVE_RIGHT, player_change_direction_sound);
	  }

	 

	for(vector<sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it)
	  (*it)->advance_by_time(dt);
	  //(*it)->set_velocity;
	resolve_collisions();
  }

  void world::draw() {
	al_clear_to_color(al_map_rgb(0,0,0));
	for(vector<sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it)
	  (*it)->draw(&camera, &view_rect);
  }

}
