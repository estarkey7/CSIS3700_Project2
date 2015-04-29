#include "obstruction_sprite.h"
#include "image_library.h"
#include "image_sequence.h"

namespace csis3700 {
  obstruction_sprite::obstruction_sprite(string name_in,float initial_x, float initial_y, float sx_in, float sy_in, ALLEGRO_BITMAP *image) : sprite(name_in,initial_x, initial_y, sx_in, sy_in) {
  	image_sequence *s = new image_sequence;
  	s->add_image(image, 0);
  	set_image_sequence(s);
  
  }

  Vector2 obstruction_sprite::get_velocity() const {
    return Vector2(0,0);
  }

  void obstruction_sprite::set_velocity(const Vector2& v) {
    assert(false);
  }

  void obstruction_sprite::resolve(const collision& collision, sprite* other) {
    // do nothing, I am not an active participant in a collision
  }

}
