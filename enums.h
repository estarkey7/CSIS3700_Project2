#ifndef ENUMS_H
#define ENUMS_H
#include "allegro5/allegro.h"
#include <cstdlib>
#include <string>

namespace csis3700 {
	static Vector2 DISPLAY_SIZE(1024, 768);
	enum character_state { ALIVE , DEAD, };
	enum character_movement { MOVE_LEFT, JUMP, MOVE_RIGHT, HOVER, IDLE };
  	enum game_state { GAME_OVER , LEVEL_ONE };
  	enum main_objects { P1_TANK , P1_MUZZLE, P2_TANK, P2_MUZZLE, PROJECTILE, EXPLOSION, MISSED };
	enum gameDifficulty {EASY, MODERATE, DIFFICULT, HARD, EXTREME, INSANE};
}
  	
#endif /* ENUMS_H */
