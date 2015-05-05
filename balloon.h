#pragma once
#ifndef _balloon_H
#define _balloon_H
#include "enemy_sprite.h"
#include "image_sequence.h"
#include "image_library.h"



namespace csis3700
{
	class balloon : public enemy_sprite
	{
	public:
		balloon(string name_in, float initial_x, float initial_y, float sx_in, float sy_in, ALLEGRO_BITMAP *image, float move_speed_in, int score_value_in);
		image_sequence  *balloon_sequence;
		virtual void advance_by_time(double dt);
		
		virtual ~balloon();
	};
}
#endif

