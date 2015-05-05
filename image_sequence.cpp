#include "image_sequence.h"
#include "allegro5/allegro.h"
#include <cassert>


namespace csis3700 {
	//  jump_sequence->add_image(image_library::get_instance()->get("player_jump1.png"), .1);
	//  sequence->draw(time, (DISPLAY_SIZE.get_x() / 2) + camera_offset.get_x(), (DISPLAY_SIZE.get_y() / 2) + camera_offset.get_y());

  image_with_offset::image_with_offset(ALLEGRO_BITMAP* i, double o) {
    image = i;
    offset = o;
  }

  image_sequence::image_sequence() {
    current = 0;
    last_change_time = 0;
    loop_index = 0;
  }

  void image_sequence::add_image(ALLEGRO_BITMAP *image, double offset) {
    assert(image != NULL);
    images.push_back(image_with_offset(image, offset));
  }

  void image_sequence::draw_current(float x, float y, float sx, float sy) {
	  if (sx == 1.0f && sy == 1.0f){
		  al_draw_bitmap(images[current].image, x, y, 0);
	  }
	  else {
		  float ImageWidth = al_get_bitmap_width(images[current].image);
		  float ImageHeight = al_get_bitmap_height(images[current].image);
		  al_draw_scaled_bitmap(images[current].image, 0, 0, ImageWidth, ImageHeight, x, y, sx * ImageWidth, sy * ImageHeight, 0);
	  }
  }

  void image_sequence::draw_current(bool hit, ALLEGRO_COLOR tint, float x, float y, float sx, float sy) {
	  if (sx == 1.0f && sy == 1.0f){
		  al_draw_tinted_bitmap(images[current].image, tint, x, y, 0);
	  }
	  else {
		  float ImageWidth = al_get_bitmap_width(images[current].image);
		  float ImageHeight = al_get_bitmap_height(images[current].image);
		  al_draw_tinted_scaled_bitmap(images[current].image, tint, 0, 0, ImageWidth, ImageHeight, x, y, sx * ImageWidth, sy * ImageHeight, 0);
	  }
  }

  void image_sequence::draw(double time, float x, float y, float sx, float sy) {
    assert(images.size() > 0);
    if (images.size() == 1) {
      draw_current(x, y, sx, sy);
      return;
    }
    image_with_offset visible = images[current];
    size_t next_index = current+1;
    if (next_index >= images.size()) {
      next_index = loop_index;
    }
    image_with_offset next = images[next_index];
    if (time - last_change_time > next.offset) {
      current = next_index;
      last_change_time = time;
    }
	draw_current(x, y,sx, sy);
  }

  void image_sequence::draw(bool hit, ALLEGRO_COLOR tint, double time, float x, float y, float sx, float sy) {
	  	  
	  assert(images.size() > 0);
	  if (images.size() == 1) 
	  {
		  if (hit == false)
		  {
			  draw_current(x, y, sx, sy);
			  return;
		  }
		  else
		  {
			  draw_current(hit, tint, x, y, sx, sy);
			  return;
		  }
		 
	  }
	  image_with_offset visible = images[current];
	  size_t next_index = current + 1;
	  if (next_index >= images.size()) {
		  next_index = loop_index;
	  }
	  image_with_offset next = images[next_index];
	  if (time - last_change_time > next.offset) {
		  current = next_index;
		  last_change_time = time;
	  }

	  if (hit == false)
	  {
		  draw_current(x, y, sx, sy);		 
	  }
	  else
	  {
		  draw_current(hit, tint, x, y, sx, sy);
	  }
	    
	  	  
  }

  int image_sequence::get_width() const {
    assert(images.size() > 0);
    return al_get_bitmap_width(images[0].image);
  }

  int image_sequence::get_height() const {
    assert(images.size() > 0);
    return al_get_bitmap_height(images[0].image);
  }

  void image_sequence::set_loop_index(size_t loop_index) {
    assert(loop_index < images.size());
    this->loop_index = loop_index;
  }

}
