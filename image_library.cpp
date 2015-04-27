#include "image_library.h"
#include <string.h>

namespace csis3700 {
  image_library *image_library::default_instance = NULL;

  image_library *image_library::get_instance() {
    if (default_instance == NULL)
      default_instance = new image_library(image_directory);
    return default_instance; 
  }

  image_library::image_library(std::string dir) {
      directory = dir;
  }

  ALLEGRO_BITMAP *image_library::get(std::string name) {
      if(images.find(name) == images.end()) load_image(name);
      return images[name];
  }

  void image_library::load_image(std::string name) {
	  /*char str[150];
	  std::string bs = "\\";
	  strcat_s(str, bs.c_str());
	  strcat_s(str, name.c_str());*/
	 // ALLEGRO_BITMAP *r = al_load_bitmap(str);
	  //		(directory + '/' + name).c_str()
	  ALLEGRO_BITMAP *r = NULL;
	  
	  r = al_load_bitmap((directory + '/' + name).c_str());
    if (r == NULL) {
      std::cerr << "Failed to load " << name << " from directory " << directory << std::endl;
      assert(false);
    }
    images[name] = r;

  }  
}
