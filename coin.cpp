#include "coin.h"

using namespace csis3700;
using namespace std;

namespace csis3700
{
	coin::coin(string name_in, float initial_x, float initial_y, float sx_in, float sy_in, ALLEGRO_BITMAP *image, float move_speed_in, int score_value_in) : enemy_sprite(name_in, initial_x, initial_y, sx_in, sy_in, image, move_speed_in, true, 0.0f)

		//enemy_sprite(string name_in, float initial_x, float initial_y, float sx_in, float sy_in, 
		//ALLEGRO_BITMAP *image, float move_speed_in, bool can_jump, float jump_amount_in, int damage_in) : phys_sprite(name_in, initial_x, initial_y, sx_in, sy_in)
	{
		coinBaseSequence = new image_sequence();
		coinSpecialSequence = new image_sequence();
		float coint_rotate_speed = .04;
		coinBaseSequence->add_image(image_library::get_instance()->get("coin1.png"), coint_rotate_speed);
		coinBaseSequence->add_image(image_library::get_instance()->get("coin2.png"), coint_rotate_speed);
		coinBaseSequence->add_image(image_library::get_instance()->get("coin3.png"), coint_rotate_speed);
		coinBaseSequence->add_image(image_library::get_instance()->get("coin4.png"), coint_rotate_speed);
		coinBaseSequence->add_image(image_library::get_instance()->get("coin5.png"), coint_rotate_speed);
		coinBaseSequence->add_image(image_library::get_instance()->get("coin6.png"), coint_rotate_speed);
		
		coinSpecialSequence = new image_sequence();
		coinSpecialSequence->add_image(image_library::get_instance()->get("dollar1.png"), coint_rotate_speed);
		coinSpecialSequence->add_image(image_library::get_instance()->get("dollar2.png"), coint_rotate_speed);
		coinSpecialSequence->add_image(image_library::get_instance()->get("dollar3.png"), coint_rotate_speed);
		coinSpecialSequence->add_image(image_library::get_instance()->get("dollar4.png"), coint_rotate_speed);
		coinSpecialSequence->add_image(image_library::get_instance()->get("dollar5.png"), coint_rotate_speed);
		coinSpecialSequence->add_image(image_library::get_instance()->get("dollar6.png"), coint_rotate_speed);

		set_image_sequence(coinBaseSequence);
		jump_amount = 170;
		is_jumping = true;
	}




	void coin::resolve(const collision& collision, sprite *other)
	{
		// collision with ground
		if (other->get_name() == "ground")
		{


			rectangle r = collision.collision_rectangle();
			set_velocity(Vector2(get_velocity().get_x(), 0.0f));
			set_position((get_position() + Vector2(0, -r.get_height()) ));

			if (is_jumping)
			{
				set_velocity(Vector2(get_velocity().get_x(), -jump_amount));
			}
		}


	}

	coin::~coin()
	{
		delete coinBaseSequence;
		delete coinSpecialSequence;
	}
}
