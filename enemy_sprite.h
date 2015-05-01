#ifndef _ENEMY_SPRITE
#define _ENEMY_SPRITE
#pragma once
#include "phys_sprite.h"
#include "image_sequence.h"
#include "image_library.h"

namespace csis3700
{
	class enemy_sprite : public phys_sprite
	{
	public:
		enemy_sprite(string name_in, float initial_x, float initial_y, float sx_in, float sy_in, ALLEGRO_BITMAP *image, float move_speed_in = 10);
		image_sequence  *staticImageSequence;
		image_sequence  *moving_sequence;
		virtual ~enemy_sprite();

	protected:
		float move_speed;

	};
}
#endif