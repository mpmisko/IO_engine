#include <stdio.h>
#include "../lib/io_lib.h"
#include "../src/renderer_main.h"

#define BACKGROUND_PATH "resources/background.jpg"
#define WINDOWWIDTH 1440
#define WINDOWHEIGHT 800

enum obj_types { empty, player };

typedef struct {
  int hp;
  int dfwd;
  int dright;
  int dleft;
  int dbckwd;
} Player;

struct local_variables {
  int id1;
  int id2;
};

bool move_fwd_cond(Game* game, env_obj_t* obj) {
  struct local_variables lv = *(struct local_variables*)game->user_variables;
  if ((obj->id == lv.id1 && game->pressed_keys[W]) ||
      (obj->id == lv.id2 && game->pressed_keys[UP])) {
    return 1;
  } else {
    return 0;
  }
}

void move_fwd(Game* game, env_obj_t* obj) {
  obj->sprite->rectangle.x -=
      round(sin(to_radians(-obj->sprite->angle)) * obj->sprite->movement_speed);
  obj->sprite->rectangle.y -=
      round(cos(to_radians(-obj->sprite->angle)) * obj->sprite->movement_speed);
}

bool move_bckwd_cond(Game* game, env_obj_t* obj) {
  struct local_variables lv = *(struct local_variables*)game->user_variables;
  if ((obj->id == lv.id1 && game->pressed_keys[S]) ||
      (obj->id == lv.id2 && game->pressed_keys[DOWN])) {
    return 1;
  } else {
    return 0;
  }
}

void move_bckwd(Game* game, env_obj_t* obj) {
  obj->sprite->rectangle.x +=
      round(sin(to_radians(-obj->sprite->angle)) * obj->sprite->movement_speed);
  obj->sprite->rectangle.y +=
      round(cos(to_radians(-obj->sprite->angle)) * obj->sprite->movement_speed);
}

bool move_left_cond(Game* game, env_obj_t* obj) {
  struct local_variables lv = *(struct local_variables*)game->user_variables;
  if ((obj->id == lv.id1 && game->pressed_keys[A]) ||
      (obj->id == lv.id2 && game->pressed_keys[LEFT])) {
    return 1;
  } else {
    return 0;
  }
}

void move_left(Game* game, env_obj_t* obj) {
     obj->sprite->angle = obj->sprite->angle - obj->sprite->rotation_speed < 0
                         ? obj->sprite->angle - obj->sprite->rotation_speed + 360
                         : obj->sprite->angle - obj->sprite->rotation_speed;
}

bool move_right_cond(Game* game, env_obj_t* obj) {
  struct local_variables lv = *(struct local_variables*)game->user_variables;
  if ((obj->id == lv.id1 && game->pressed_keys[D]) ||
      (obj->id == lv.id2 && game->pressed_keys[RIGHT])) {
    return 1;
  } else {
    return 0;
  }
}

void move_right(Game* game, env_obj_t* obj) {
     obj->sprite->angle = obj->sprite->angle + obj->sprite->rotation_speed >= 360
                         ? obj->sprite->angle + obj->sprite->rotation_speed - 360
                         : obj->sprite->angle + obj->sprite->rotation_speed;
}

int main(void) {
  Game* game = init_game();  // create window

  set_background(game, BACKGROUND_PATH);

  // draw the image to the window
  // First draw texture to the copy of renderer and then swap the buffers

  struct local_variables lv;

  Player p1 = {100, 0, 0, 0, 0};

  // create sprites
  lv.id1 = add_object(game, &p1, empty,
                      get_sprite(WINDOWWIDTH / 3, WINDOWHEIGHT / 2,
                                 "resources/sprite1.png", game));

  Player p2 = {100, 0, 0, 0, 0};
  lv.id2 = add_object(game, &p2, empty,
                      get_sprite(2 * WINDOWWIDTH / 3, WINDOWHEIGHT / 2,
                                 "resources/sprite2.png", game));

  add_single_listener(game, move_fwd_cond, move_fwd);
  add_single_listener(game, move_bckwd_cond, move_bckwd);
  add_single_listener(game, move_left_cond, move_left);
  add_single_listener(game, move_right_cond, move_right);

  game->user_variables = &lv;

  start_game(game);

  // Clean Up
  printf("cleaning up\n");
  delete_game(game);
}
