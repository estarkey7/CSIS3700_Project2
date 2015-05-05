#ifndef _ENEMY_SPRITE
#define _ENEMY_SPRITE
#pragma once
#include "phys_sprite.h"
#include "image_sequence.h"
#include "image_library.h"
#include "collision.h"
#include "Vector2.h"
#include "allegro5\allegro_primitives.h"
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include <cmath>
#include <string>
#include <cstdlib> 
#include <iostream>
#include <queue>
#include "enums.h"



namespace csis3700
{
	class enemy_sprite : public phys_sprite
	{
	public:
		enemy_sprite(string name_in, float initial_x, float initial_y, float sx_in, float sy_in, ALLEGRO_BITMAP *image, float move_speed_in = 10, bool can_jump = false, float jump_amount_in = 60, int damage_in = 10, bool ai_on_in = false, Vector2 *follow_target_in = NULL);
		image_sequence  *staticImageSequence;
		image_sequence  *movingImageSequence;
		virtual ~enemy_sprite();

		virtual void resolve(const collision& collision, sprite *other);
		void setMoveSpeed(double speed);
		void moveEnemy();
		virtual void advance_by_time(double dt);
		virtual bool is_passive() const;
		

	protected:
		bool ai_on;
		Vector2 * target;
		float jump_amount;
		bool is_jumping;
		float friction = 0;
		float frictionLimit = 40.0f;
		float moveSpeed;
		float maxMoveSpeed = 100;
		Vector2 gravity = Vector2(0.0, 450);

		ALLEGRO_SAMPLE_INSTANCE *bugCrawlingSampleInstance;
		ALLEGRO_SAMPLE *bugCrawlingSample;

	};
}
#endif