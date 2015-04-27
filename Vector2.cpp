#include "Vector2.h"
#include <cmath>
using namespace std;

namespace csis3700 {
    

  void Vector2::Set(float new_x, float new_y){
  	x = new_x;
  	y = new_y;
  }
  
  
  Vector2 operator*(const double d, const Vector2& v) {
    return Vector2(d*v.get_x(),d*v.get_y());
  }
  
  Vector2 Vector2::operator+(const Vector2& other) const {
    return Vector2(get_x()+other.get_x(), get_y()+other.get_y());
  }

  Vector2 Vector2::operator-(const Vector2& other) const {
    return Vector2(get_x()-other.get_x(), get_y()-other.get_y());
  }
  
  bool Vector2::operator==(const Vector2& other) const {
    return get_x() == other.get_x() && get_y() == other.get_y();
  }
  
  Vector2 Vector2::Max(const Vector2& other) const {
    return Vector2(fmax(x,other.x), fmax(y, other.y));
  }
  
  Vector2 Vector2::Min(const Vector2& other) const {
    return Vector2(fmin(x,other.x), fmin(y, other.y));
  }

  std::ostream& operator<<(std::ostream& outs, const Vector2& v) {
    outs << v.get_x() << ", " << v.get_y();
    return outs;
  }

  Vector2 Vector2::clamp(float max_x, float max_y) const {
    float tmp_x = x;
    float tmp_y = y;
    if (fabs(x) > max_x)
      tmp_x = ((x > 0 ? 1 : -1) * max_x);
    if (fabs(y) > max_y)
      tmp_y = ((y > 0 ? 1 : -1) * max_y);
    return Vector2(tmp_x, tmp_y);
  }

  Vector2& Vector2::operator+=(const Vector2& other) {
    x += other.x;
    y += other.y;
    return *this;
  }


  
}
