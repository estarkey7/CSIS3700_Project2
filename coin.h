#pragma once
#ifndef _COIN_H
#define _COIN_H
#include "enemy_sprite.h"
#include "image_sequence.h"
#include "image_library.h"



namespace csis3700
{
	static int coins_created = 0;
	class coin : public enemy_sprite
	{
	public:
		coin(string name_in, float initial_x, float initial_y, float sx_in, float sy_in, ALLEGRO_BITMAP *image, float move_speed_in, int score_value_in);
		image_sequence  *coinBaseSequence;
		image_sequence  *coinSpecialSequence;
		void coin::resolve(const collision& collision, sprite *other);
		virtual ~coin();
	};
}
#endif

