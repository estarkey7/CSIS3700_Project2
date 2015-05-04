#include "enemy_sprite.h"

using namespace csis3700;
using namespace std;

namespace csis3700
{
	enemy_sprite::enemy_sprite(string name_in, float initial_x, float initial_y, float sx_in, float sy_in, ALLEGRO_BITMAP *image, float move_speed_in) : phys_sprite(name_in, initial_x, initial_y, sx_in, sy_in)
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
		moveEnemy();
	}

	void enemy_sprite::resolve(const collision& collision, sprite *other)
	{
		// collision with ground
		if (other->get_name() == "ground")
		{
			rectangle r = collision.collision_rectangle();
			set_position((get_position() + Vector2(0, -r.get_height())));

			// WHEN PLAYERS VELOCITY IS ALMOST 0(WITHIN FRICTION THRESHHOLD AMOUNT OF 0), SET IT TO EXACTLY 0;
			//	IF ITS NOT CLOSE, APPLY FRICTION
			if (get_velocity().get_x() > -frictionLimit && get_velocity().get_x() < frictionLimit)
			{
				set_velocity((Vector2(0.0f, 0.0f)));
				set_image_sequence(staticImageSequence);
			}
			else
			{
				set_velocity(Vector2(get_velocity().get_x() * friction, 0.0f));
			}

			/*if (get_velocity().get_x() > frictionLimit)
			{
			set_image_sequence(walk_right_sequence);
			al_play_sample_instance(walk_sound_instance);
			}
			else if (get_velocity().get_x() < -friction_threshhold)
			{
			set_image_sequence(walk_left_sequence);
			al_play_sample_instance(walk_sound_instance);
			}*/
		}
		/*else  if (other->get_name() == "balloon"){
		move(JUMP);
		set_velocity(get_velocity() + Vector2(0.0f, -500.0f));
		other->set_position(Vector2(-10000, -5000));
		}*/

	}

	bool enemy_sprite::isPassive() const 
	{
		return false;
	}

	void enemy_sprite::advance_by_time(double dt) {
		phys_sprite::advance_by_time(dt);
				

		Vector2 gravityStep = (dt * gravity);
		set_velocity((get_velocity() + gravityStep));
		Vector2 stepVelocity = (dt * get_velocity());
		set_position((get_position() + stepVelocity));

	}

	void enemy_sprite::moveEnemy()
	{
		if (get_velocity().x > -maxMoveSpeed)
		{
			set_velocity(get_velocity() + Vector2(-moveSpeed, 0));
			//al_play_sample_instance(bugCrawlingSampleInstance);
		}

		if (get_velocity().x > -maxMoveSpeed)
		{
			set_velocity(get_velocity() + Vector2(-moveSpeed, 0));
		}

	}

	void enemy_sprite::setMoveSpeed(double speed)
	{
		moveSpeed = speed;
	}


	enemy_sprite::~enemy_sprite()
	{
		delete staticImageSequence;
	}

}