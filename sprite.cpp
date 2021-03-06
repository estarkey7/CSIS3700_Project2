#include "sprite.h"

namespace csis3700 {

  // CONSTRUCTOR
	sprite::sprite(string name_in, float initial_x, float initial_y,float sx_in, float sy_in) {
	name = name_in;
	position = Vector2(initial_x, initial_y);
	time = 0;
	register_sprite_id();
	sx = sx_in;
	sy = sy_in;
	
	
	
	// PRINT INITALIZATION VARIABLE INFO FOR DEBUGGING 
	if (name_in == "enemy")
	print_initial_configuration();
  }

  // get_name  
  string sprite::get_name() {
    return name;
  } 
  
  // register_sprite_id
  void sprite::register_sprite_id(){
  	sprite_id_count++;
  	sprite_id = sprite_id_count;
  }
  
  // get_sprite_id
  int sprite::get_sprite_id(){
  	return sprite_id;
  }

  // get_sprite_id_count
  int sprite::get_sprite_id_count(){
	  return sprite_id_count;
  }
  
  void sprite::print_initial_configuration(){
  	// PRINT OBJECT STATISTICS
  		cout << "**********SPRITE CREATED**********" << endl;
		cout << "----NAME          : " << get_name() << endl;
		cout << "----SPRITE_ID     : " << get_sprite_id() << endl;
		cout << "----TRANSFORM       " << endl;
		cout << "--------POSITION    " << endl;
		cout << "------------X     : " << get_x() << endl;
		cout << "------------Y     : " << get_y() << endl;
		cout << "------------X_Loc : " << get_x_local() << endl;
		cout << "------------Y_Loc : " << get_y_local() << endl << endl;
  }  
  
  // set_image_sequence
  void sprite::set_image_sequence(image_sequence *s) {
    sequence = s;
  }
   
  // DECONTRUCTOR  
  sprite::~sprite() {
  }

  /*
  // get_center
  Vector2 sprite::get_center(){
  	return  Vector2( position.x + (get_width() / 2.0f), position.y - (get_height() / 2.0f));
  }
  */
  
  // get_width
  int sprite::get_width() const {
    return sequence->get_width();
  }

  // get_height
  int sprite::get_height() const {
    return sequence->get_height();
  }

  // get_x
  float sprite::get_x() const {
    return position.get_x();
  }

  // get_y
  float sprite::get_y() const {
    return position.get_y();
  }

  // get_x
  float sprite::get_x_local()  {
	  
	  // return  position.get_x() + camera.get_x() - (1024 / 2);
	  return  (x_local);
	  
  }

  // get_y 
  float sprite::get_y_local()  {
	  //return   position.get_y() + camera.get_y() + (768 / 2);
	  return  (y_local);
  }

  // draw
  void sprite::draw(Vector2 *camera_in) {
	  if (visible)
	  sequence->draw(time, (-camera_in->get_x() + (DISPLAY_SIZE.get_x() / 2)) + position.get_x(), (-camera_in->get_y() + DISPLAY_SIZE.get_y() / 2) + position.get_y(), sx, sy);

	  x_local = -camera_in->get_x() + (DISPLAY_SIZE.get_x() / 2) + position.get_x();
	  y_local = (-camera_in->get_y() + DISPLAY_SIZE.get_y() / 2) + position.get_y();
  }

  // bounding_box
  rectangle sprite::bounding_box() const {
    return rectangle(position, get_width() * sx, get_height() * sy);
  }

  // collision_rectangle
  rectangle sprite::collision_rectangle(const sprite& other) const {
    return bounding_box().intersection(other.bounding_box());
  }

  // collides_with
  bool sprite::collides_with(const sprite& other) const {
    return !collision_rectangle(other).is_degenerate();
  }

  // advance_by_time
  void sprite::advance_by_time(double dt) {
    time += dt;
  }

  // is_passive
  bool sprite::is_passive() const {
    return true;
  }

  // get_position
  Vector2 sprite::get_position() const {
    return position;
  }

  // set_position
  void sprite::set_position(Vector2 p) {
    position = p;
  }

  void sprite::set_passive(bool is_passive_in)
  {
	  passive = is_passive_in;
  }

  void sprite::set_visible(bool is_visible_in)
  {
	  visible = is_visible_in;
  }
  bool sprite::get_visible(){ return visible; }

  void sprite::set_score_value(int score_value_in){ score_value = score_value_in; }
  int sprite::get_score_value(){ return score_value; }
}
