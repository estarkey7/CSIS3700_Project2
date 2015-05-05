#include "player_sprite.h"
#include "image_library.h"
#include "image_sequence.h"
#include "collision.h"
#include "allegro5\allegro_primitives.h"



using namespace std;

namespace csis3700 {

	void repeat_char(char c, int n){
		for (int i = 0; i<n; i++) cout << c;

	}

	void clear_screen(){
		for (int i = 0; i < 100; i++)
			cout << endl;
	}

	void splash_screen(){
		cout << endl;
		for (int i = 0; i<3; i++){
			cout << "   ";
			repeat_char('*', 28);
			cout << endl;
		}

		for (int i = 0; i<3; i++){
			cout << "   ";
			if (i == 1){
				repeat_char('*', 6);   //
				cout << " -MAIN  PLAYER- ";
				repeat_char('*', 6);
			}
			else {
				repeat_char('*', 6);
				repeat_char(' ', 16);
				repeat_char('*', 6);
			}
			cout << endl;
		}

		for (int i = 0; i<3; i++){
			cout << "   ";
			repeat_char('*', 28);
			cout << endl;
		}									 //
		cout << "   ***      PROJECT  2      ***" << endl << "   ";
		repeat_char('*', 28);
		cout << endl << endl << endl << endl;
	}

  player_sprite::player_sprite(string name_in,float initial_x, float initial_y, float sx_in, float sy_in,
						ALLEGRO_BITMAP *image, float move_speed_in,
						float max_move_speed_in, float jump_speed_in, Vector2 *camera_in,
						ALLEGRO_SAMPLE_INSTANCE *player_landing_sound_instance_in,
						ALLEGRO_SAMPLE_INSTANCE *change_direction_sound_instance_in,
						ALLEGRO_SAMPLE_INSTANCE *walk_sound_instance_in) :
							phys_sprite(name_in,initial_x, initial_y, sx_in, sy_in) {

			// CREATE IDLE_SEQUENCE (DEFAULT)
		  idle_sequence = new image_sequence;
		  //idle_sequence->add_image(image, .1);
		  idle_sequence->add_image(image_library::get_instance()->get("alien_idle01.png"), .2);
		  idle_sequence->add_image(image_library::get_instance()->get("alien_idle02.png"), .2);
		  
		  // CREATE walk_right_SEQUENCE (DEFAULT)
		  walk_right_sequence = new image_sequence;
		  double walk_animation_speed = .045;
		  walk_right_sequence->add_image(image_library::get_instance()->get("alien_walk_right1.png"), walk_animation_speed );
		  walk_right_sequence->add_image(image_library::get_instance()->get("alien_walk_right2.png"), walk_animation_speed );
		  walk_right_sequence->add_image(image_library::get_instance()->get("alien_walk_right3.png"), walk_animation_speed );
		  walk_right_sequence->add_image(image_library::get_instance()->get("alien_walk_right4.png"), walk_animation_speed );
		  walk_right_sequence->add_image(image_library::get_instance()->get("alien_walk_right5.png"), walk_animation_speed );
		  walk_right_sequence->add_image(image_library::get_instance()->get("alien_walk_right6.png"), walk_animation_speed );
		  walk_right_sequence->add_image(image_library::get_instance()->get("alien_walk_right7.png"), walk_animation_speed );
		  walk_right_sequence->add_image(image_library::get_instance()->get("alien_walk_right8.png"), walk_animation_speed );
		  walk_right_sequence->add_image(image_library::get_instance()->get("alien_walk_right9.png"), walk_animation_speed );

		  // CREATE walk_left_SEQUENCE (DEFAULT)
		  walk_left_sequence = new image_sequence;

		  walk_left_sequence->add_image(image_library::get_instance()->get("alien_walk_left1.png"), walk_animation_speed);
		  walk_left_sequence->add_image(image_library::get_instance()->get("alien_walk_left2.png"), walk_animation_speed);
		  walk_left_sequence->add_image(image_library::get_instance()->get("alien_walk_left3.png"), walk_animation_speed);
		  walk_left_sequence->add_image(image_library::get_instance()->get("alien_walk_left4.png"), walk_animation_speed);
		  walk_left_sequence->add_image(image_library::get_instance()->get("alien_walk_left5.png"), walk_animation_speed);
		  walk_left_sequence->add_image(image_library::get_instance()->get("alien_walk_left6.png"), walk_animation_speed);
		  walk_left_sequence->add_image(image_library::get_instance()->get("alien_walk_left7.png"), walk_animation_speed);
		  walk_left_sequence->add_image(image_library::get_instance()->get("alien_walk_left8.png"), walk_animation_speed);
		  walk_left_sequence->add_image(image_library::get_instance()->get("alien_walk_left9.png"), walk_animation_speed);


		    // SET IDLE SEQUENCE AS INITIAL SEQUENCE
		  set_image_sequence(idle_sequence);

		    // CREATE JUMP SEQUENCE
		  jump_sequence = new image_sequence;
		  jump_sequence->add_image(image_library::get_instance()->get("alien_jump1.png"), .3);
		  jump_sequence->add_image(image_library::get_instance()->get("alien_jump2.png"), .4);
		  jump_sequence->add_image(image_library::get_instance()->get("alien_jump3.png"), 1.5);
		  jump_sequence->add_image(image_library::get_instance()->get("alien_jump4.png"), .2);

		  player_movement_state = IDLE;
		  move_speed = move_speed_in;		// INCREMENT SPEED AT WHICH THE PLAYERS HORIZONTAL VELOCITY INCREASES PER MOVEMENT CALL
		  move_speed_default = move_speed_in;
		  max_move_speed = max_move_speed_in; // MAX HORIZONTAL VELOCITY LIMIT THAT THE PLAYERS MOVEMENT FUNCTIONS CAN REACH
		  max_move_speed_default = max_move_speed_in;
		  jump_speed = jump_speed_in; // JUMP STRENGTH
		  srand((unsigned int)clock() * 3305193169);
		  player_landing_sound_instance = player_landing_sound_instance_in; // SOUND FX FOR JUMPING
		  change_direction_sound_instance = change_direction_sound_instance_in; // SOUND FX FOR JUMPING
		  walk_sound_instance = walk_sound_instance_in;
		  hover_sound = al_load_sample("jump.wav");

		  fly_strength = 0;
		  score = 0; // initialize score
		  y_min_bounds = DISPLAY_SIZE.get_y() + 300;	// The y value that triggers a respawn. "value = 768(bottom of display) + amount below the screen"
		  hover_strength = .6;
		  hover_strength_default = .6;
		  gravity = Vector2(0.0, 450);	// Declare the Gravity Vector, For each second(dt), accelerate the velocity 450 pixels towards the floor
		  camera_offset.Set(0, 0); // PIXEL OFF USED TO CONTROLL WHERE THE "BITMAP IMAGE" OF THE PLAYER IS DRAWN FROM THE CENTER OF THE DISPLAY
		  respawn_location.Set(343, (DISPLAY_SIZE.get_y() - 50) - 250);	// HARDCODED LOCATION VECTOR TO RESET THE PLAYERS LOCATION TO THE BEGGINING OF LEVEL 1
		  friction = .9f;	// FRICTION FROM PLAYER MOVING ON GROUND
		  friction_threshhold = 40.0f;	// PLAYER WILL STOP MOVING ON GROUND IF PLAYERS HORIZONTAL VELOCITY IS WITHIN THE ABSOLUTE VALUE OF THIS THRESH HOLD 
		 
		  gotCoinSample = al_load_sample("drip.wav");
		  gotCoinSampleInstance = al_create_sample_instance(gotCoinSample);
		  al_attach_sample_instance_to_mixer(gotCoinSampleInstance, al_get_default_mixer());
		 
		  

		  camera_in->Set(position.get_x() - camera_offset.get_x(), position.get_y() - camera_offset.get_y());
		  respawn();

		  
  }

  void player_sprite::set_score(int i){ score = i; }
  void player_sprite::add_score(int i){ score += i; }
  int player_sprite::get_health(){ return health; }
  void player_sprite::set_health(int h){ health = h; }
  void  player_sprite::add_health(int h){ health += h; }
  void  player_sprite::remove_health(int h)
  {
	  // remove health but don't let it become negative
	  if (h <= health)
	  {
		  health -= h;
	  }
	  else
	  {
		  health = 0;
	  }
  
	  // DIE
	  if (health == 0)
	  {
		  is_alive = false;
	  }
  
  }
  int player_sprite::get_score(){ return score; }


  bool player_sprite::is_passive() const {
		  return false;
  }

  void player_sprite::set_on_ground(bool v) {
		  on_ground = v;
  }

  void player_sprite::respawn(ALLEGRO_SAMPLE_INSTANCE *sound_in) {
	  set_health(100);
	  is_alive = true;
	  set_position(respawn_location);
	  set_velocity(Vector2(0, 0));
	  fly_strength = 0;
	  hover_strength = hover_strength_default;
	  move_speed = move_speed_default;
	  max_move_speed = max_move_speed_default;
	  if (sound_in != NULL)
		  al_play_sample_instance(sound_in);
  }

  void player_sprite::print_initial_configuration(){
	  // PRINT OBJECT STATISTICS
	  splash_screen();	// Prints a Box that makes the player object easier to find in the command line cout statements
	  cout << "**********SPRITE CREATED**********" << endl;
	  cout << "----NAME          : " << get_name() << endl;
	  cout << "----SPRITE_ID     : " << get_sprite_id() << " OUT OF : " << get_sprite_id_count() << endl;
	  cout << "----TRANSFORM       " << endl;
	  cout << "--------POSITION    " << endl;
	  cout << "------------X     : " << get_x() << endl;
	  cout << "------------Y     : " << get_y() << endl;
	  cout << "------------X_Loc : " << get_x_local() << endl;
	  cout << "------------Y_Loc : " << get_y_local() << endl;
	  cout << "--------VECLOCITY   " << endl;
	  cout << "------------X     : " << get_velocity().get_x() << endl;
	  cout << "------------Y     : " << get_velocity().get_y() << endl;
	  cout << "--------SCALE     : " << endl;
	  cout << "------------SX    : " << sx << endl;
	  cout << "------------SY    : " << sy << endl << endl;
  }
 
  void player_sprite::advance_by_time(double dt) {
		  phys_sprite::advance_by_time(dt);

		  
		  // MAKE PLAYER RESPAWN IF PLAYER FALLS BELOW THE y_min_bounds value
		  if (position.get_y() > y_min_bounds){

			  is_alive = false;
			  
		  }


		  /*	THESE PLAYER LOCATION CHECKS dont apply if the screen is scrolling. 
			    (THEY CHECK THE PLAYERS LOCATION WITHIN THE DISPLAY)

					  // HARDCODED RESPAWN FOR LEFT BOUNDS (OF DISPLAY, not world)
					  if (position.get_x() < -51){
						  set_position(Vector2(1024 + 50, position.get_y()));
					  }

					  // HARDCODED RESPAWN FOR RIGHT BOUNDS (OF DISPLAY, not world). 
					  if (position.get_x() > 1024 +51){
						  set_position(Vector2(-50, position.get_y()));  
					  }
		  */

		// GRAVITY PHYSICS  CODE FROM GAME EXAMPLE ON CLASS SITE:
		
		  // Scale the acceleration down to the size of the current timestep
		  Vector2 gravityStep = (dt * gravity);
		  set_velocity( ( get_velocity() + gravityStep) );
		  Vector2 stepVelocity = (dt * get_velocity());
		  set_position( (get_position() + stepVelocity));
		  
		  
		  //CHECK IF PLAYER IS DEAD
		  if (is_alive == false)
		  {
			  respawn();

		  }
  }

  void player_sprite::resolve(const collision& collision, sprite *other) {
	  if (other->get_name() == "background")
	  {
		  // APPLY A LITTLE FRICTION WHILE JUMPING
		  set_velocity(		Vector2( get_velocity().get_x() * .97f, get_velocity().get_y() )		);
	  }
	  // collision with ground
	  else if(other->get_name() == "ground"){
		  rectangle r = collision.collision_rectangle();
		  
		  set_position((get_position() + Vector2(0, -r.get_height())));
		  //set_velocity((Vector2(get_velocity().get_x(), 0.0f)));

		  // IF PLAYER FALLS FASTER THAN A VELOCITY OF 300 DOWN, MAKE A THUMP ON LANDING
		  if (get_velocity().get_y() >300 && get_velocity().get_y() != 0)
			  al_play_sample_instance(player_landing_sound_instance);

		  // WHEN PLAYERS VELOCITY IS ALMOST 0(WITHIN FRICTION THRESHHOLD AMOUNT OF 0), SET IT TO EXACTLY 0;
		  //	IF ITS NOT CLOSE, APPLY FRICTION
		  if (get_velocity().get_x() > -friction_threshhold && get_velocity().get_x() < friction_threshhold){
			  set_velocity((Vector2(0.0f , 0.0f)));
			  player_movement_state = IDLE;
			  set_image_sequence(idle_sequence);
		  }
		  else {
			  set_velocity( Vector2(get_velocity().get_x() * friction,  0.0f) );
		  }

		  if (get_velocity().get_x() > friction_threshhold )
		  {
			  set_image_sequence(walk_right_sequence);
			  al_play_sample_instance(walk_sound_instance);
		  }
		  else if (get_velocity().get_x() < -friction_threshhold)
		  {
			  set_image_sequence(walk_left_sequence);
			  al_play_sample_instance(walk_sound_instance);
		  }
	  }
	  else  if (other->get_name() == "enemy"){
		  cout << "HIT BY ENEMY (ID #" << other->get_sprite_id() << " )." << endl;
		  if (other->is_passive() == false)
		  {
			  remove_health(other->get_score_value());
			  playerHit = true;
		  }
			  
		  other->set_passive(true);
		  
		  // if visible is false, this object will be deleted on next world.advance_by_time iteration of sprites
		  other->set_visible(false);

	  }
	  else  if (other->get_name() == "balloon"){
		  if (get_velocity().y<0)
			  set_velocity(Vector2(get_velocity().get_x(), 0));
		  set_velocity(get_velocity() + Vector2(0.0f, -450.0f));

		  other->set_visible(false);
	  }
	  else  if (other->get_name() == "solid_balloon"){
		  if (get_velocity().y<0)
			  set_velocity(Vector2(get_velocity().get_x(), 0));
		  set_velocity(get_velocity() + Vector2(0.0f, -450.0f));

		  
	  }
	  else  if (other->get_name() == "magic_balloon"){
		  move(JUMP);
		  hover_strength = 0;
		  fly_strength = -200;
		  move_speed += 100;
		  max_move_speed += 75;
		  set_velocity(get_velocity() + Vector2(0.0f, -100.0f));
		  other->set_position(Vector2(-10000, -5000));
	  }
	  else if (other->get_name() == "coin"){
		  cout << "Collected coin (ID #" << other->get_sprite_id() << " )." << endl;
		  if (other->is_passive() == false)
			  add_score(other->get_score_value());

		  other->set_passive(true);	// stops collisions with object

		  other->set_visible(false); // deletes object
		  al_play_sample_instance(gotCoinSampleInstance);
	  }

	  if (other->get_name() == "winning_platform"){
		  rectangle r = collision.collision_rectangle();

		  set_position((get_position() + Vector2(0, -r.get_height())));
		  //set_velocity((Vector2(get_velocity().get_x(), 0.0f)));

		  // IF PLAYER FALLS FASTER THAN A VELOCITY OF 300 DOWN, MAKE A THUMP ON LANDING
		  if (get_velocity().get_y() >300 && get_velocity().get_y() != 0)
			  al_play_sample_instance(player_landing_sound_instance);

		  // WHEN PLAYERS VELOCITY IS ALMOST 0(WITHIN FRICTION THRESHHOLD AMOUNT OF 0), SET IT TO EXACTLY 0;
		  //	IF ITS NOT CLOSE, APPLY FRICTION
		  if (get_velocity().get_x() > -friction_threshhold && get_velocity().get_x() < friction_threshhold){
			  set_velocity((Vector2(0.0f, 0.0f)));
			  player_movement_state = IDLE;
			  set_image_sequence(idle_sequence);
		  }
		  else {
			  set_velocity(Vector2(get_velocity().get_x() * friction, 0.0f));
		  }

		  if (get_velocity().get_x() > friction_threshhold)
		  {
			  set_image_sequence(walk_right_sequence);
			  al_play_sample_instance(walk_sound_instance);
		  }
		  else if (get_velocity().get_x() < -friction_threshhold)
		  {
			  set_image_sequence(walk_left_sequence);
			  al_play_sample_instance(walk_sound_instance);
		  }
		  player_has_won = true;
		  
	  }
	  else
	  {
		  player_has_won = false;
	  }
  }
  
  
  void player_sprite::jump(ALLEGRO_SAMPLE_INSTANCE *sound_in) {
  
		// INCREASE VELOCITY UPWARDS IF VELOCITY IS 0 (NOT JUMPING)
	  if (get_velocity().y == 0){
		  set_image_sequence(jump_sequence);
		  // add force upwards
		  // al_play_sample(jump_sound, .3f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, NULL);
		  set_velocity(get_velocity() + Vector2(0, -jump_speed));
		  player_movement_state = JUMP;
		  
		  if (sound_in != NULL)
			  al_play_sample_instance(sound_in);
		  
	  }
  }

  void player_sprite::hover(ALLEGRO_SAMPLE_INSTANCE *sound_in) {

	  // INCREASE VELOCITY UPWARDS IF VELOCITY IS 0 (NOT JUMPING)
	  if (get_velocity().y >= 0){
		  // add force upwards
		  //al_play_sample(jump_sound, .3f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, NULL);
		  set_velocity(Vector2(get_velocity().get_x(), get_velocity().get_y() * hover_strength + fly_strength));

		  if (sound_in != NULL)
			  al_play_sample_instance(sound_in);
	  }
  }
  
  void player_sprite::walk_left(ALLEGRO_SAMPLE_INSTANCE *sound_in){
		// SNAP VELOCITY TO 0 IF CHANGING DIRECTIONS
	  if (get_velocity().x > 0){
		  set_velocity(Vector2(0, get_velocity().y));
		  if (sound_in != NULL)
			  al_play_sample_instance(sound_in);
	  }
	  
		// INCREASE VELOCITY TO THE LEFT IF VELOCITY HASN'T REACHED MAX_MOVE_SPEED YET
		  if(get_velocity().x > -max_move_speed)
			set_velocity(get_velocity() + Vector2(-move_speed, 0));
  }
  
  void player_sprite::walk_right(ALLEGRO_SAMPLE_INSTANCE *sound_in){
		// SNAP VELOCITY TO 0 IF CHANGING DIRECTIONS
	  if ( get_velocity().x < 0 ) {
		  set_velocity(Vector2(0, get_velocity().y));
		  if (sound_in != NULL)
			  al_play_sample_instance(sound_in);
	  }
		
		// INCREASE VELOCITY TO THE RIGHT IF VELOCITY HASN'T REACHED MAX_MOVE_SPEED YET
	  if (get_velocity().x < max_move_speed )
			set_velocity(get_velocity()  + Vector2(move_speed, 0));

		  
  }
  
  void player_sprite::move(character_movement direction, ALLEGRO_SAMPLE_INSTANCE *sound_in){
		// add force
	  	  
		  switch (direction){
			    case   MOVE_LEFT:    walk_left(sound_in);   break;
								 
				case  MOVE_RIGHT:   walk_right(sound_in);   break;
								 
				case       JUMP :         jump(sound_in);   break;	

				case       HOVER:        hover(sound_in);   break;
		   }

		 
  }

  void player_sprite::draw(Vector2 *camera_in){
	  static bool setTime = false;
	  static double timeCaptured = 0;
	  double result = 0;
	  // (1024.0f / 2.0f) - 300, (768.0f / 2) + 100
	  if (setTime == false && playerHit == false)
	  {
		  sequence->draw(time, (DISPLAY_SIZE.get_x() / 2) + camera_offset.get_x(), (DISPLAY_SIZE.get_y() / 2) + camera_offset.get_y(), sx, sy);

	  }
	  else
	  {
		  if (playerHit == true)
		  {
			  if (setTime == false)
			  {
				  timeCaptured = time;
				  setTime = true;
			  }
		  }


		  ALLEGRO_COLOR tint;
		  result = time - timeCaptured;
		  result = result * .2;
		  tint = al_map_rgba(255, result * 225, result * 225, result);
		  sequence->draw(true, tint, time, (DISPLAY_SIZE.get_x() / 2) + camera_offset.get_x(), (DISPLAY_SIZE.get_y() / 2) + camera_offset.get_y(), sx, sy);
		  if (result >= 1)
		  {
			  setTime = false;
			  playerHit = false;
			  timeCaptured = 0.0;
		  }
	  }
	  

	  //sequence->draw(time, get_x(), get_y());
	  camera_in->Set(position.get_x() - camera_offset.get_x(), position.get_y() - camera_offset.get_y());
	  
	  if (player_has_won)
		  al_draw_filled_circle((DISPLAY_SIZE.get_x() / 2), (DISPLAY_SIZE.get_y() / 2), 500, al_map_rgba(15, randomGenerator(100, 150), 15, randomGenerator(0, 50)));
		  
  }

  int player_sprite::randomGenerator(int min, int max)
  {
	  static int previous = 0;

	  while (1)
	  {
		  //Seed rnd number. This is not working correctly.

		  if (previous != rand() % (max - min + 1) + min)
		  {
			  previous = rand() % (max - min + 1) + min;
			  return rand() % (max - min + 1) + min;
			  break;
		  }
	  }
  }
  

  

  player_sprite::~player_sprite()
  {
	  delete idle_sequence;
	  delete walk_right_sequence;
	  delete walk_left_sequence;
	  delete jump_sequence;
  }
  
 
} // end of csis3700 namespace



































