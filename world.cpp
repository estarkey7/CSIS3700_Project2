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
	  game_music = al_load_sample("game_music.wav");
	  jump_sound = al_load_sample("jump.wav");
	  al_play_sample(game_music, .4f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, NULL);
	  obstruction_sprite *splash = new obstruction_sprite("splash", 0, 0, image_library::get_instance()->get("splash.png"));
	obstruction_sprite *ground = new obstruction_sprite("ground",(1024.0f /2.0f) - 20.0f, 768.0f - 50  ,image_library::get_instance()->get("ground.png"));
	  sprites.push_back(splash); 
	  make_ground();
	player = new player_sprite("alien", (1024.0f / 2.0f) - 400.0f, (768.0f - 50) - 100, image_library::get_instance()->get("player.png"), 300.0f, 300.0f, 400.0f, jump_sound);
	
	 player->s->add_image(image_library::get_instance()->get("player_idle2.png"), .2);
	 
	
	sprites.push_back(player);
  
  }

  void world::make_ground(){
	  for (int i = 0; i < 1024; i += 50){
			
		  if (i <= 400 || i > 800)
			  sprites.push_back(new obstruction_sprite("ground", i , 768.0f - 50, image_library::get_instance()->get("ground.png")));
	  }

	  for (int i = 550; i < 1024 - 300; i += 50){

		  sprites.push_back(new obstruction_sprite("ground", i, 768.0f - 250, image_library::get_instance()->get("ground.png")));
	  }
	  //Test
	  
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
	al_destroy_sample(jump_sound); 
	
  }

  void world::handle_event(ALLEGRO_EVENT ev) {
	if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
		

		switch (ev.keyboard.keycode){
				case ALLEGRO_KEY_A :  player->move(MOVE_LEFT); break;
								 
				case ALLEGRO_KEY_S:   player->move(HOVER); break;
								 
				case ALLEGRO_KEY_D :  player->move(MOVE_RIGHT); break;
								 
				case ALLEGRO_KEY_W:  player->move(JUMP); break;			  
								 
				case ALLEGRO_KEY_LEFT : player->move(MOVE_LEFT); break;
								 
				case ALLEGRO_KEY_RIGHT :  player->move(MOVE_RIGHT);break;
				
				case ALLEGRO_KEY_UP :  player->move(JUMP); break;
				
				case ALLEGRO_KEY_DOWN:  player->move(HOVER); break;
				
				case ALLEGRO_KEY_SPACE :  break;
												
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
	for(vector<sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it)
	  (*it)->advance_by_time(dt);
	  //(*it)->set_velocity;
	resolve_collisions();
  }

  void world::draw() {
	al_clear_to_color(al_map_rgb(5,5,5));
	for(vector<sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it)
	  (*it)->draw();
  }

}
