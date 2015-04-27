#include "rectangle.h"
#include "Vector2.h"

namespace csis3700 {

  rectangle::rectangle(float x, float y, float width, float height) {
    init(x,y,width,height);
  }

  rectangle::rectangle(Vector2 corner, float width, float height) {
    init(corner.get_x(), corner.get_y(), width, height);
  }

  rectangle::rectangle(Vector2 upper_left_corner, Vector2 lower_right_corner) {
    init(upper_left_corner.get_x(),
         upper_left_corner.get_y(),
         lower_right_corner.get_x() - upper_left_corner.get_x(),
         lower_right_corner.get_y() - upper_left_corner.get_y());
  }

  void rectangle::init(float x, float y, float width, float height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
  }

  float rectangle::get_width() const {
    return width;
  }

  float rectangle::get_height() const {
    return height;
  }

  float rectangle::get_area() const {
    return get_width() * get_height();
  }

  bool rectangle::contains(Vector2 point) const {
    return point.get_x() <= x + width && point.get_x() >= x &&
      point.get_y() <= y + height && point.get_y() >= y;
  }

  Vector2 rectangle::upper_left_corner() const {
    return Vector2(x,y);
  }

  Vector2 rectangle::lower_right_corner() const {
    return Vector2(x+width,y+height);
  }

  rectangle rectangle::intersection(const rectangle& other) const {
    return rectangle(upper_left_corner().Max(other.upper_left_corner()),
                     lower_right_corner().Min(other.lower_right_corner()));
  }

  bool rectangle::is_degenerate() const {
    return width < 0 || height < 0;
  }

}
