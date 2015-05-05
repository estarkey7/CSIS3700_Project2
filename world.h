#ifndef __CDS_WORLD_H
#define __CDS_WORLD_H

#include "allegro5/allegro.h"
#include "sprite.h"
#include "phys_sprite.h"
#include "player_sprite.h"
#include "obstruction_sprite.h"
#include <vector>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include "allegro5\allegro_font.h"
#include "allegro5\allegro_ttf.h"
#include "keyboard_manager.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include "Vector2.h"
#include "enums.h"
#include "enemy_sprite.h"
#include "coin.h"
#include "balloon.h"

namespace csis3700 {
	
  class world {
  public:
  
    /**
     * Construct the world. The display is passed in simply to make it
     * possible to modify options or access the backbuffer. DO NOT
     * store the display in an instance variable. DO NOT start drawing
     * on the screen. Just load bitmaps etc.
     */
    
	world(size_t width_in, size_t height_in, ALLEGRO_DISPLAY *display);

    /**
     * Free any resources being used by the world.
     */
    ~world();

    /**
     * Block the copy constructor.  Worlds should not be copied to
     * just assert(false)
     */
    world(const world& other);

    /**
     * Block operator =.  Worlds should not be assigned.
     */
   /* world& operator =(const world& other);*/
 
    /**
     * Update the state of the world based on the event ev.
     */
    void handle_event(ALLEGRO_EVENT ev);

    /**
     * Advance the state of the world forward by the specified time.
     */
    void advance_by_time(double dt);

    /**
     * Draw the world. Note that the display variable is passed only
     * because it might be needed to switch the target bitmap back to
     * the backbuffer.
     */
    void draw();
	void fade();
	void getPlayerPosition(int x, int y) const;

	void make_ground(int level_in);

  private:

    void resolve_collisions();

	void build_platform(
						int init_x = 0, 
						int init_y = 0,
						int x_scale = 1,
						int y_scale = 1,
						string object_name_in = "ground", 
						string object_location_string_in = "ground.png",
						int object_width_in = 50, 
						int object_height_in = 50 
						);

	void build_background(int init_x, int init_y, int width);

    player_sprite *player;
	int enemy_count = 0;
	ALLEGRO_SAMPLE *game_music;
	ALLEGRO_SAMPLE *jump_sound;
	ALLEGRO_SAMPLE *player_change_direction_sound;
	ALLEGRO_SAMPLE *player_landing_sound;
	ALLEGRO_SAMPLE *walk_sound;
	ALLEGRO_SAMPLE_INSTANCE *jump_sound_instance;
	ALLEGRO_SAMPLE_INSTANCE *player_change_direction_sound_instance;
	ALLEGRO_SAMPLE_INSTANCE *player_landing_sound_instance;
	ALLEGRO_SAMPLE_INSTANCE *walk_sound_instance;
	ALLEGRO_FONT *rapier12 = al_load_font("Rapier Zero.ttf", 12, 0);
	ALLEGRO_FONT *rapier24 = al_load_font("Rapier Zero.ttf", 24, 0);
	ALLEGRO_FONT *rapier32 = al_load_font("Rapier Zero.ttf", 32, 0);
	ALLEGRO_FONT *rapier48 = al_load_font("Rapier Zero.ttf", 48, 0);
	ALLEGRO_DISPLAY *gameDisplay;
    std::vector<sprite*> sprites;
	 Vector2 camera;
	 
	 keyboard_manager Key_Input;

	 std::queue<Vector2> enemySpawnLocationQueue;
	 gameDifficulty difficultyLevel;
	 void createEnemies();
	 void addEnemeySpawnVectors();
	 std::vector<enemy_sprite*> enemies;
	 void checkForEnemySpawn();
	 bool messageBoxAlreadyShown = false;
	 int randomGenerator(int minQty, int maxQty);
	 void simple_balloon(float x, float y, bool is_solid = false);
	 void createCoins();
  };
}

#endif /* WORLD_H */
