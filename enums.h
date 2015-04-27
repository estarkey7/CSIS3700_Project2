#ifndef ENUMS_H
#define ENUMS_H
#include "allegro5/allegro.h"
#include <cstdlib>
#include <string>

namespace csis3700 {
	enum character_state { IDLE , RUNNING , JUMPING , DEAD, };
	enum character_movement { MOVE_LEFT, JUMP, MOVE_RIGHT, HOVER };
  	enum game_state { GAME_OVER , LEVEL_ONE };
  	enum main_objects { P1_TANK , P1_MUZZLE, P2_TANK, P2_MUZZLE, PROJECTILE, EXPLOSION, MISSED };
}
  	
#endif /* ENUMS_H */
