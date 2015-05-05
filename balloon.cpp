#include "balloon.h"

using namespace csis3700;
using namespace std;

namespace csis3700
{
	balloon::balloon(string name_in, float initial_x, float initial_y, float sx_in, float sy_in, ALLEGRO_BITMAP *image, float move_speed_in, int score_value_in) : enemy_sprite(name_in, initial_x, initial_y, sx_in, sy_in, image, move_speed_in, true, 0.0f)

		//enemy_sprite(string name_in, float initial_x, float initial_y, float sx_in, float sy_in, 
		//ALLEGRO_BITMAP *image, float move_speed_in, bool can_jump, float jump_amount_in, int damage_in) : phys_sprite(name_in, initial_x, initial_y, sx_in, sy_in)
	{
		balloon_sequence = new image_sequence();
		
		image_sequence *balloon_sequence = new image_sequence;
		double balloon_animation_speed = .4;
		balloon_sequence->add_image(image_library::get_instance()->get("balloon1.png"), balloon_animation_speed);
		balloon_sequence->add_image(image_library::get_instance()->get("balloon2.png"), balloon_animation_speed);
		set_image_sequence(balloon_sequence);



		set_image_sequence(balloon_sequence);
		
		is_jumping = false;
	}



	void balloon::advance_by_time(double dt) {
		phys_sprite::advance_by_time(dt);

	}

	balloon::~balloon()
	{
		delete balloon_sequence;
		
	}
}
