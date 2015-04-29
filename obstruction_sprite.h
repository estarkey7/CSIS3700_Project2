#ifndef __CDS_OBSTRUCTION_SPRITE_H
#define __CDS_OBSTRUCTION_SPRITE_H

#include "sprite.h"
using namespace std;
namespace csis3700 {

  /**
   * obstruction_sprites don't typically move and when they
   * participate in a collision they are unimpacted by it. They
   * typically render themslves as a single, static bitmap.
   */
  class obstruction_sprite : public sprite {
  public:
    obstruction_sprite(string name_in,float initial_x, float initial_y, float sx_in, float sy_in, ALLEGRO_BITMAP *image=NULL);
    virtual void set_velocity(const Vector2& v);
    virtual Vector2 get_velocity() const;
    virtual void resolve(const collision& collision, sprite* other);
  };
}


#endif /* OBSTRUCTION_SPRITE_H */
