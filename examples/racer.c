#include <stdio.h>
#include <stdlib.h>
#include "../lib/io_lib.h"
#include "../src/renderer_main.h"

#define BACKGROUND_PATH "resources/racer/map.png"
#define WINDOWWIDTH 1440
#define WINDOWHEIGHT 800

enum obj_types { empty, player, shot };

typedef struct {
  int hp;
  int dfwd;
  int dright;
  int dleft;
  int dbckwd;
  double rotation_speed;
  int movement_speed;
} Player;

typedef struct {
  int movement_speed;
} Shot;


struct local_variables {
  int id1;
  int id2;
};

bool detect_black(Game* game, env_obj_t* obj) {
  return ((obj->type == player) &&
          is_black(
              game,
              obj->sprite->rectangle.x + get_center(obj->sprite->rectangle).x,
              obj->sprite->rectangle.y + get_center(obj->sprite->rectangle).y));
}

bool detect_not_black(Game* game, env_obj_t* obj) {
  return ((obj->type == player) &&
          !is_black(
              game,
              obj->sprite->rectangle.x + get_center(obj->sprite->rectangle).x,
              obj->sprite->rectangle.y + get_center(obj->sprite->rectangle).y));
}

void slow_down(Game* game, env_obj_t* obj) {
  ((Player*)obj->object)->movement_speed = 1;
}

void speed_up(Game* game, env_obj_t* obj) {
  ((Player*)obj->object)->movement_speed = 12;
}

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
  obj->sprite->rectangle.x -= round(sin(to_radians(-obj->sprite->angle)) *
                                    ((Player*)obj->object)->movement_speed);
  obj->sprite->rectangle.y -= round(cos(to_radians(-obj->sprite->angle)) *
                                    ((Player*)obj->object)->movement_speed);
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
  obj->sprite->rectangle.x += round(sin(to_radians(-obj->sprite->angle)) *
                                    ((Player*)obj->object)->movement_speed);
  obj->sprite->rectangle.y += round(cos(to_radians(-obj->sprite->angle)) *
                                    ((Player*)obj->object)->movement_speed);
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
  obj->sprite->angle =
      obj->sprite->angle - ((Player*)obj->object)->rotation_speed < 0
          ? obj->sprite->angle - ((Player*)obj->object)->rotation_speed + 360
          : obj->sprite->angle - ((Player*)obj->object)->rotation_speed;
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
  obj->sprite->angle =
      obj->sprite->angle + ((Player*)obj->object)->rotation_speed >= 360
          ? obj->sprite->angle + ((Player*)obj->object)->rotation_speed - 360
          : obj->sprite->angle + ((Player*)obj->object)->rotation_speed;
}


int main(void) {
  Game* game = init_game();  // create window

  set_background(game, BACKGROUND_PATH);

  // draw the image to the window
  // First draw texture to the copy of renderer and then swap the buffers

  struct local_variables lv;

  Player p1 = {100, 0, 0, 0, 0, 7.5, 12};

  // create sprites
  lv.id1 = add_object(game, &p1, player,
                      get_sprite(100, 700,
                                 "resources/sprite1.png", game));

  Player p2 = {100, 0, 0, 0, 0, 7.5, 12};
  lv.id2 = add_object(game, &p2, player,
                      get_sprite(150, 700,
                                 "resources/sprite2.png", game));

  add_single_listener(game, move_fwd_cond, move_fwd);
  add_single_listener(game, move_bckwd_cond, move_bckwd);
  add_single_listener(game, move_left_cond, move_left);
  add_single_listener(game, move_right_cond, move_right);
  add_single_listener(game, detect_black, slow_down);
  add_single_listener(game, detect_not_black, speed_up);


  game->user_variables = &lv;

  start_game(game);

  // Clean Up
  printf("cleaning up\n");
  delete_game(game);
}
