#include "sprite.h"
#include "phys_sprite.h"
#include <vector>
using namespace std;

namespace csis3700 {
  
  phys_sprite::phys_sprite(string name_in,float initial_x, float initial_y, float initial_vx, float initial_vy) : sprite(name_in,initial_x, initial_y) {
    velocity = Vector2(initial_vx, initial_vy); 
    
  }

  void phys_sprite::advance_by_time(double dt) {
    sprite::advance_by_time(dt);
    position = position + dt * velocity;
    velocity = velocity + dt * get_acceleration();
  }

  void phys_sprite::set_velocity(const Vector2& v) {
    velocity = v;
  }

  Vector2 phys_sprite::get_acceleration() const {
    Vector2 a(0,0);
    for(vector<Vector2>::const_iterator it = forces.begin(); it != forces.end(); ++it)
      a += *it;
    return a;
  }

  Vector2 phys_sprite::get_velocity() const {
    return velocity;
  }

  void phys_sprite::add_force(Vector2 f) {
    forces.push_back(f);
  }

}

