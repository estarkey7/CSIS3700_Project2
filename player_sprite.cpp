#include "player_sprite.h"
#include "image_library.h"
#include "image_sequence.h"
#include "collision.h"


using namespace std;

namespace csis3700 {

  player_sprite::player_sprite(string name_in,float initial_x, float initial_y,
						ALLEGRO_BITMAP *image, float move_speed_in,
						float max_move_speed_in, float jump_speed_in, ALLEGRO_SAMPLE *jump_sound_in, ALLEGRO_SAMPLE *change_dir_sound_in ) :
							phys_sprite(name_in,initial_x, initial_y) {
							
		  s = new image_sequence;
		  s->add_image(image, .1);
		  set_image_sequence(s);
		  move_speed = move_speed_in;
		  max_move_speed = max_move_speed_in;
		  jump_speed = jump_speed_in;
		  // Declare the Gravity Vector, For each second(dt), accelerate the velocity 450 pixels towards the floor
		  gravity = Vector2(0.0, 450);
		  jump_sound = jump_sound_in;
  }

  bool player_sprite::is_passive() const {
		  return false;
  }

  void player_sprite::set_on_ground(bool v) {
		  on_ground = v;
  }
 
  void player_sprite::advance_by_time(double dt) {
		  phys_sprite::advance_by_time(dt);

		  // HARDCODED RESPAWN
		  if (position.get_y() > 768 + 300){
			  set_position(Vector2((1024.0f / 2.0f) - 400.0f, (768.0f - 50) - 100));
			  set_velocity(Vector2(0, 0));
		  }

		  // HARDCODED RESPAWN
		  if (position.get_x() < -51){
			  set_position(Vector2(1024 + 50, position.get_y()));
		  }

		  // HARDCODED RESPAWN
		  if (position.get_x() > 1024 +51){
			  set_position(Vector2(-50, position.get_y()));  
		  }

		// Scale the acceleration down to the size of the current timestep
		  Vector2 gravityStep = (dt * gravity);
		  set_velocity( ( get_velocity() + gravityStep) );
		  Vector2 stepVelocity = (dt * get_velocity());
		  set_position( (get_position() + stepVelocity));
  }

  void player_sprite::resolve(const collision& collision, sprite *other) {
		// collision
	  if (other->get_name() == "ground"){
		  rectangle r = collision.collision_rectangle();
		  set_position((get_position() + Vector2(0, -r.get_height())));
		  set_velocity((Vector2(get_velocity().get_x(), 0.0f)));
	  }
  }
  
  
  void player_sprite::jump() {
  
		// INCREASE VELOCITY UPWARDS IF VELOCITY IS 0 (NOT JUMPING)
	  if (get_velocity().y == 0){
		  // add force upwards
		  al_play_sample(jump_sound, .3f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, NULL);
		  set_velocity(get_velocity() + Vector2(0, -jump_speed));
		  
	  }
  }

  void player_sprite::hover() {

	  // INCREASE VELOCITY UPWARDS IF VELOCITY IS 0 (NOT JUMPING)
	  if (get_velocity().y >= 0){
		  // add force upwards
		  al_play_sample(jump_sound, .3f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, NULL);
		  set_velocity(Vector2(get_velocity().get_x(), -3  ));

	  }
  }
  
  void player_sprite::walk_left(){
		// SNAP VELOCITY TO 0 IF CHANGING DIRECTIONS
		   if(get_velocity().x > 0)
			set_velocity( Vector2(0, get_velocity().y));
	  
		// INCREASE VELOCITY TO THE LEFT IF VELOCITY HASN'T REACHED MAX_MOVE_SPEED YET
		  if(get_velocity().x > -max_move_speed)
			set_velocity(get_velocity() + Vector2(-move_speed, 0));
  }
  
  void player_sprite::walk_right(){
		// SNAP VELOCITY TO 0 IF CHANGING DIRECTIONS
		  if(get_velocity().x < 0)
			set_velocity( Vector2(0, get_velocity().y));
		
		// INCREASE VELOCITY TO THE RIGHT IF VELOCITY HASN'T REACHED MAX_MOVE_SPEED YET
		  if(get_velocity().x < max_move_speed)
			set_velocity(get_velocity() + Vector2(move_speed, 0));
  }
  
  void player_sprite::move(character_movement direction){
		// add force
		  switch (direction){
				case  MOVE_LEFT :    walk_left();   break;
								 
				case MOVE_RIGHT :   walk_right();   break;
								 
				case       JUMP :         jump();   break;	

				case       HOVER:         hover();   break;
			   }
		
  
  }

} // end of csis3700 namespace



































