#include "enemy_sprite.h"

using namespace csis3700;
using namespace std;

enemy_sprite::enemy_sprite(string name_in, float initial_x, float initial_y, float sx_in, float sy_in, ALLEGRO_BITMAP *image, float move_speed_in) : phys_sprite(name_in, initial_x, initial_y, sx_in, sy_in)
{
	staticImageSequence = new image_sequence();
	staticImageSequence->add_image(image_library::get_instance()->get("bug_static1.png"), .3);
	staticImageSequence->add_image(image_library::get_instance()->get("bug_static2.png"), .3);
	staticImageSequence->add_image(image_library::get_instance()->get("bug_static3.png"), .3);
	staticImageSequence->add_image(image_library::get_instance()->get("bug_static2.png"), .3);
	staticImageSequence->add_image(image_library::get_instance()->get("bug_static1.png"), .3);
}


enemy_sprite::~enemy_sprite()
{
}
