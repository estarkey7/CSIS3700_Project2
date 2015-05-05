#include "coin.h"

using namespace csis3700;
using namespace std;

namespace csis3700
{
	coin::coin(string name_in, float initial_x, float initial_y, float sx_in, float sy_in, ALLEGRO_BITMAP *image, float move_speed_in) : enemy_sprite(name_in, initial_x, initial_y, sx_in, sy_in, image, move_speed_in)
	{
		cointBaseSequence = new image_sequence();
		cointBaseSequence->add_image(image_library::get_instance()->get("coin1.png"), .1);
		cointBaseSequence->add_image(image_library::get_instance()->get("coin2.png"), .1);
		cointBaseSequence->add_image(image_library::get_instance()->get("coin3.png"), .1);
		cointBaseSequence->add_image(image_library::get_instance()->get("coin4.png"), .1);
		cointBaseSequence->add_image(image_library::get_instance()->get("coin5.png"), .1);
		cointBaseSequence->add_image(image_library::get_instance()->get("coin6.png"), .1);
		cointBaseSequence->add_image(image_library::get_instance()->get("coin7.png"), .1);
		cointBaseSequence->add_image(image_library::get_instance()->get("coin6.png"), .1);
		cointBaseSequence->add_image(image_library::get_instance()->get("coin5.png"), .1);

		coinSpecialSequence->add_image(image_library::get_instance()->get("dollar1.png"), .1);
		coinSpecialSequence->add_image(image_library::get_instance()->get("dollar2.png"), .1);
		coinSpecialSequence->add_image(image_library::get_instance()->get("dollar3.png"), .1);
		coinSpecialSequence->add_image(image_library::get_instance()->get("dollar4.png"), .1);
		coinSpecialSequence->add_image(image_library::get_instance()->get("dollar5.png"), .1);
		coinSpecialSequence->add_image(image_library::get_instance()->get("dollar6.png"), .1);
		coinSpecialSequence->add_image(image_library::get_instance()->get("dollar7.png"), .1);
		coinSpecialSequence->add_image(image_library::get_instance()->get("dollar6.png"), .1);
		coinSpecialSequence->add_image(image_library::get_instance()->get("dollar5.png"), .1);

		set_image_sequence(cointBaseSequence);
		score_value = 10;
	}


	void coin::resolve(const collision& collision, sprite *other) 
	{
		// collision with ground
		if (other->get_name() == "ground")
		{


			rectangle r = collision.collision_rectangle();
			set_velocity(Vector2(get_velocity().get_x(), 0.0f));
			set_position((get_position() + Vector2(0, -r.get_height() -20)));

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
		

	}

	coin::~coin()
	{
	}
}
