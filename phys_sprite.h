#ifndef __CDS_PHYS_SPRITE_H
#define __CDS_PHYS_SPRITE_H

#include <vector>
#include "sprite.h"

namespace csis3700 {

  /**
   * Physical sprites move using an approximation of newtonian 
   * kinematics.
   */
  class phys_sprite : public sprite {
  public:
    phys_sprite(string name_in,float initial_x=0, float initial_y=0, float sx_in = 1.0f, float sy_in = 1.0f , float initial_vx=0, float initial_vy=0);

    virtual void advance_by_time(double dt);

    virtual Vector2 get_acceleration() const;
    //virtual void set_acceleration(const Vector2& a);

    virtual Vector2 get_velocity() const;
    virtual void set_velocity(const Vector2& v);

    virtual void add_force(Vector2 f);

  private:
    Vector2 velocity;
    std::vector<Vector2> forces;
  };
}
#endif /* PHYS_SPRITE_H */
