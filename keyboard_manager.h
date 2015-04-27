#ifndef __CDS_KEYBOARD_MANAGER_H
#define __CDS_KEYBOARD_MANAGER_H
#include <set>

namespace csis3700 {
  class keyboard_manager {
  public:
    static keyboard_manager *get_instance();

    keyboard_manager();

    /**
     * Answers true iff the specified key currently held down
     */
    bool is_key_down(int keycode);

    /**
     * Called when a key is pressed
     */
    void key_down(int keycode);

    /**
     * Called when a key is released
     */
    void key_up(int keycode);

  private:
    static keyboard_manager *default_instance;
    std::set<int> down;
  };
}

#endif /* __CDS_KEYBOARD_MANAGER_H */
