#ifndef __CDS_PLAYER_SPRITE_H
#define __CDS_PLAYER_SPRITE_H
#include "phys_sprite.h"
#include "image_sequence.h"
#include "Vector2.h"
#include <cmath>
#include <string>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include <cstdlib> 
#include <iostream>
#include <queue>
#include "enemy_sprite.h"

namespace csis3700 {
  class player_sprite : public phys_sprite {
  public:
	  image_sequence  *idle_sequence;
	  image_sequence  *jump_sequence;
	  image_sequence  *walk_right_sequence;
	  image_sequence  *walk_left_sequence;
	  character_movement player_movement_state;
  
	player_sprite(string name_in, float initial_x = 0, float initial_y = 0, float sx_in = 1.0f, float sy_in = 1.0f, 
				  ALLEGRO_BITMAP *image = NULL, float move_speed_in = 10, 
				  float max_move_speed_in = 50, float jump_speed_in = 200,
				   Vector2 *camera_in = NULL,
				  ALLEGRO_SAMPLE_INSTANCE *player_landing_sound_instance_in = NULL,
				  ALLEGRO_SAMPLE_INSTANCE *change_direction_sound_instance_in = NULL, ALLEGRO_SAMPLE_INSTANCE *walk_sound_instance_in = NULL);

    virtual bool is_passive() const;
    virtual void set_on_ground(bool v);
    virtual void advance_by_time(double dt);
    virtual void resolve(const collision& collision, sprite* other);
	virtual void jump(ALLEGRO_SAMPLE_INSTANCE *sound_in = NULL);
	virtual void hover(ALLEGRO_SAMPLE_INSTANCE *sound_in = NULL);
	virtual void walk_left(ALLEGRO_SAMPLE_INSTANCE *sound_in = NULL);
	virtual void walk_right(ALLEGRO_SAMPLE_INSTANCE *sound_in = NULL);
	virtual void respawn(ALLEGRO_SAMPLE_INSTANCE *sound_in = NULL);
	virtual void move(character_movement direction, ALLEGRO_SAMPLE_INSTANCE *sound_in = NULL);
	void draw(Vector2 *camera_in);
	void print_initial_configuration();
	void set_score(int i);
	void add_score(int i);
	int get_score();
	virtual ~player_sprite();
	void setDifficulty(gameDifficulty difficulty);
    
    
  private:
	  float fly_strength;
	int score = 0;
    bool on_ground;
    float move_speed;
    float max_move_speed;
	float hover_strength;
	float move_speed_default;
	float max_move_speed_default;
	float hover_strength_default;
	float friction;
	float friction_threshhold;
    float jump_speed;
	float y_min_bounds;
    Vector2 gravity;
	Vector2 camera_offset;
	Vector2 respawn_location;
	ALLEGRO_SAMPLE_INSTANCE *player_landing_sound_instance;
	ALLEGRO_SAMPLE_INSTANCE *change_direction_sound_instance;
	ALLEGRO_SAMPLE_INSTANCE *walk_sound_instance;
	ALLEGRO_SAMPLE *hover_sound;
	std::queue<Vector2> enemySpawnLocationQueue;
	gameDifficulty difficultyLevel;
	void createEnemies(Vector2 initialPosition);
	void addEnemeySpawnVectors();
	std::vector<enemy_sprite*> enemies;
  };
}


#endif /* PLAYER_SPRITE_H */ 
