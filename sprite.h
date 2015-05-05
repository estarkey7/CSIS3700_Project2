#ifndef __CDS_SPRITE_H
#define __CDS_SPRITE_H
#include "allegro5/allegro.h"
#include "image_sequence.h"
#include "Vector2.h"
#include "rectangle.h"
#include <cstdlib> 
#include <string>
#include <iostream>
#include "enums.h"

using namespace std;

namespace csis3700 {

  static int sprite_id_count = 0;
  
  class collision;
	
  class sprite {
  public:
	  
	  
	  sprite(string name_in, float initial_x, float initial_y, float sx, float sy);

    void set_image_sequence(image_sequence *s);

    /**
     * Destructor
     */
    virtual ~sprite();
 

    /**
     * these two should cause errors, no copying!
     */
    sprite(const sprite& other) { assert(false); }
    
    sprite& operator =(const sprite& other) { assert(false); }
    
    virtual string get_name() ;
    
    virtual void print_initial_configuration();
    
    virtual void register_sprite_id();
    
    virtual int get_sprite_id();
	virtual int get_sprite_id_count();

    virtual int get_width() const;

    virtual int get_height() const;

    virtual float get_x() const;

    virtual float get_y() const;

	virtual float get_x_local();

	virtual float get_y_local();

    
    // virtual Vector2 get_center() const;

    virtual Vector2 get_position() const;

    virtual void set_position(Vector2 p);

    virtual Vector2 get_velocity() const = 0;

    virtual void set_velocity(const Vector2& v) = 0;

    virtual bool is_passive() const;	
	
    /**
     * Draw this sprite.
     */
	virtual void draw(Vector2 *camera_in);

    /**
     * Returns true iff I collide with other. Default implementation
     * returns true iff my bounding box overlaps other's.
     */
    virtual bool collides_with(const sprite& other) const;


    /**
     * Move time forward by the specified amount
     */
    virtual void advance_by_time(double dt);

    /**
     * Return this sprite's bounding box
     */
    virtual rectangle bounding_box() const;

    /**
     * Return the intersection of this sprite's bounding box with
     * other's bounding box.
     */
    virtual rectangle collision_rectangle(const sprite& other) const;

    virtual void resolve(const collision& collision, sprite* other) = 0;
    
	image_sequence* getImageSequence() { return sequence; }
	void set_passive(bool is_passive_in);
	void set_visible(bool is_visible_in);
	bool get_visible();
	void set_score_value(int score_value_in);
	int get_score_value();

  protected:
	  bool visible = true;
	  bool passive = false;
	  int score_value = 0;
	  float x_local = 0.0f;
	  float y_local = 0.0f;
	  float sx;
	  float sy;
  	int sprite_id;
	
  	
	string name;
    
    /**
     * My position
     */
	Vector2 position;
    

    /**
     * My current image sequence
     */
    image_sequence *sequence;

    /**
     * The time in seconds since the world began ticking
     */
    double time;
  };
}
#endif /* SPRITE_H */
