#ifndef __CDS_VECTOR2_H
#define __CDS_VECTOR2_H
#include <ostream>

namespace csis3700 {

  /**
   * A 2-dimensional vector. Also used for point-like operations in
   * which case, as a point, this vector is interpreted as the point
   * corresponding to its endpoint if it began at the origin (that is
   * a point with coordinates (x,y)).
   */
  class Vector2 {
  public:
  	
  	float magnitude;
  	float sqrMagnitude;
  	float x,y;
  	
    Vector2(float initial_x=0, float initial_y=0) {
      x = initial_x;
      y = initial_y;
    }
    
    float get_x() const { return x; }
    
    float get_y() const { return y; }
    
    /**
     * Set x and y components of an existing Vector
     */
    void Set(float new_x, float new_y);

    /**
     * The vector sum of this and other.
     */
    Vector2 operator+(const Vector2& other) const;

    /**
     * The vector difference (this - other)
     */
    Vector2 operator-(const Vector2& other) const;

    /**
     * Two vectors are equal iff their components are exactly equal.
     * Be careful with floats!
     */
    bool operator==(const Vector2& other) const;

    /**
     * Return a vector whose x is the max of this.x and other.x and
     * whose y is the max of this.y and other.y.
     */
    Vector2 max(const Vector2& other) const;

    /**
     * Return a vector whose x is the min of this.x and other.x and
     * whose y is the min of this.y and other.y.
     */
    Vector2 min(const Vector2& other) const;

    /**
     * Return a vector whose x component is between -max_x and max_x
     * and whose y component is between -max_y and max_y.  If the
     * condition on the component is already met, do nothing to it,
     * otherwise set it to the max with the appropriate sign.
     */
    Vector2 clamp(float max_x, float max_y) const;

    Vector2& operator+=(const Vector2& other);

  private:
    
  };

  /**
   * Make it easy to display points.
   */
  std::ostream& operator<<(std::ostream& outs, const Vector2& v);

  /**
   * The product of a scalar and a vector (scales both components by d).
   */
  Vector2 operator*(const double d, const Vector2& v);

}


#endif /* Vector2_H */
