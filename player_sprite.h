#ifndef __CDS_PLAYER_SPRITE_H
#define __CDS_PLAYER_SPRITE_H
#include "phys_sprite.h"
#include "image_sequence.h"
#include "Vector2.h"
#include <cmath>
#include <string>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>


namespace csis3700 {
  class player_sprite : public phys_sprite {
  public:
	  image_sequence  *s;
  
	player_sprite(string name_in, float initial_x = 0, float initial_y = 0, 
				  ALLEGRO_BITMAP *image = NULL, float move_speed_in = 10, 
				  float max_move_speed_in = 50, float jump_speed_in = 200,
				  ALLEGRO_SAMPLE *jump_sound_in = NULL,
				  ALLEGRO_SAMPLE *change_dir_sound_in = NULL);

    virtual bool is_passive() const;
    virtual void set_on_ground(bool v);
    virtual void advance_by_time(double dt);
    virtual void resolve(const collision& collision, sprite* other);
    virtual void jump();
	virtual void hover();
    virtual void walk_left();
    virtual void walk_right();
	virtual void respawn();
    virtual void move(character_movement direction);
	void draw(Vector2 *camera_in, Vector2 *view_rect_in);

    
    
  private:
    bool on_ground;
    float move_speed;
    float max_move_speed;
    float jump_speed;
	float y_min_bounds;
    Vector2 gravity;
	Vector2 camera_offset;
	Vector2 respawn_location;
	ALLEGRO_SAMPLE *jump_sound;
	ALLEGRO_SAMPLE *change_direction_sound;
	

  };
}


#endif /* PLAYER_SPRITE_H */ 
