#include "enemy_sprite.h"

using namespace csis3700;
using namespace std;

namespace csis3700
{
	enemy_sprite::enemy_sprite(string name_in, float initial_x, float initial_y, float sx_in, float sy_in, ALLEGRO_BITMAP *image, float move_speed_in, bool can_jump, float jump_amount_in, int damage_in, bool ai_on_in,Vector2 *follow_target_in) : phys_sprite(name_in, initial_x, initial_y, sx_in, sy_in)
	{
		staticImageSequence = new image_sequence();
		staticImageSequence->add_image(image_library::get_instance()->get("bug_static1.png"), .3);
		staticImageSequence->add_image(image_library::get_instance()->get("bug_static2.png"), .3);
		staticImageSequence->add_image(image_library::get_instance()->get("bug_static3.png"), .3);
		staticImageSequence->add_image(image_library::get_instance()->get("bug_static2.png"), .3);
		staticImageSequence->add_image(image_library::get_instance()->get("bug_static1.png"), .3);

		movingImageSequence = new image_sequence();
		movingImageSequence->add_image(image_library::get_instance()->get("bug_run1.png"), .1);
		movingImageSequence->add_image(image_library::get_instance()->get("bug_run2.png"), .1);
		movingImageSequence->add_image(image_library::get_instance()->get("bug_run3.png"), .1);
		movingImageSequence->add_image(image_library::get_instance()->get("bug_run2.png"), .1);
		movingImageSequence->add_image(image_library::get_instance()->get("bug_run1.png"), .1);

		set_image_sequence(movingImageSequence);

		bugCrawlingSample = al_load_sample("bug.wav");
		bugCrawlingSampleInstance = al_create_sample_instance(bugCrawlingSample);
		al_attach_sample_instance_to_mixer(bugCrawlingSampleInstance, al_get_default_mixer());
		moveSpeed = move_speed_in;
		moveEnemy();
		is_jumping = can_jump;
		jump_amount = jump_amount_in;
		score_value = damage_in;
		ai_on = ai_on_in;
		target = follow_target_in;
	}



	void enemy_sprite::resolve(const collision& collision, sprite *other)
	{
		// collision with ground
		if (other->get_name() == "ground")
		{


			rectangle r = collision.collision_rectangle();
			set_velocity(Vector2(get_velocity().get_x(), 0.0f));
			set_position((get_position() + Vector2(0, -r.get_height())));

			// WHEN PLAYERS VELOCITY IS ALMOST 0(WITHIN FRICTION THRESHHOLD AMOUNT OF 0), SET IT TO EXACTLY 0;
			//	IF ITS NOT CLOSE, APPLY FRICTION
			if (get_velocity().get_x() > -frictionLimit && get_velocity().get_x() < frictionLimit)
			{
				//set_velocity(Vector2(get_velocity().get_x(), 0.0f));
				//set_image_sequence(staticImageSequence);
			}
			else
			{
				//set_velocity(Vector2(get_velocity().get_x() * friction, 0.0f));
			}

			
			if (is_jumping)
			{
				set_velocity(Vector2(get_velocity().get_x(), -jump_amount));
			}
		}
		
		
	}
	

	bool enemy_sprite::is_passive() const 
	{
		return passive;
	}

	void enemy_sprite::advance_by_time(double dt) {
		phys_sprite::advance_by_time(dt);
				

		Vector2 gravityStep = (dt * gravity);
		set_velocity((get_velocity() + gravityStep));
		Vector2 stepVelocity = (dt * get_velocity());
		set_position((get_position() + stepVelocity));
		
		if (position.get_y() > DISPLAY_SIZE.get_y() + 300)
		{
			set_visible(false);
		}

		if (ai_on == true)
		{
			if (target->get_x() > position.x){
				if (get_velocity().x < 0)
				{
					set_velocity(Vector2(-(get_velocity().x), get_velocity().y));
				}
				
			}
			else if (target->get_x() < position.x)
			{
				if (get_velocity().x > 0)
				{
					set_velocity(Vector2(-(get_velocity().x), get_velocity().y));
				}
			}
			

		}
		

	}

	void enemy_sprite::moveEnemy()
	{
		if (get_velocity().x > -maxMoveSpeed && get_velocity().x < maxMoveSpeed)
		{
			
				set_velocity(get_velocity() + Vector2(-moveSpeed, 0));
				//al_play_sample_instance(bugCrawlingSampleInstance);
			
		}


	}

	void enemy_sprite::setMoveSpeed(double speed)
	{
		moveSpeed = speed;
	}


	enemy_sprite::~enemy_sprite()
	{
		delete staticImageSequence;
		delete movingImageSequence;
	}

}