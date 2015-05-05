#pragma once
#include "enemy_sprite.h"
#ifndef _COIN_H
#define _COIN_H

namespace csis3700
{
	class coin : public enemy_sprite
	{
	public:
		coin(string name_in, float initial_x, float initial_y, float sx_in, float sy_in, ALLEGRO_BITMAP *image, float move_speed_in);
		image_sequence  *cointBaseSequence;
		image_sequence  *coinSpecialSequence;

		virtual void resolve(const collision& collision, sprite* other);
		virtual ~coin();
	};
}
#endif

