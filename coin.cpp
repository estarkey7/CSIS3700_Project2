#include "coin.h"

using namespace csis3700;
using namespace std;

namespace csis3700
{
	coin::coin(string name_in, float initial_x, float initial_y, float sx_in, float sy_in, ALLEGRO_BITMAP *image, float move_speed_in) : enemy_sprite(name_in, initial_x, initial_y, sx_in, sy_in, image, move_speed_in)
	{
		cointBaseSequence = new image_sequence();
		cointBaseSequence->add_image(image_library::get_instance()->get("coin1.png"), .3);
		/*cointBaseSequence->add_image(image_library::get_instance()->get("bug_static2.png"), .3);
		cointBaseSequence->add_image(image_library::get_instance()->get("bug_static3.png"), .3);
		cointBaseSequence->add_image(image_library::get_instance()->get("bug_static2.png"), .3);
		cointBaseSequence->add_image(image_library::get_instance()->get("bug_static1.png"), .3);*/
	}


	coin::~coin()
	{
	}
}
