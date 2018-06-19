#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "../src/utils/linked_list/linked_list.h"

#ifndef IO_LIB_H
#define IO_LIB_H

#define SINGLE_ARG_LISTENER 1
#define DOUBLE_ARG_LISTENER 2

typedef enum {WASD, arrow_key_mode, IJKL} control_mode_t;;

typedef struct controls {
  bool shooting;
  control_mode_t control_mode;
} controls_t;

// end game
// delete from game

typedef struct sprite_o {
  int x;
  int y;
  int speed;
} obj_sprite_t;

typedef struct sprite_g {
  int speed;
  int fps;
} game_sprite_t;

typedef struct environment_object {
  int type;
  void *object;
  obj_sprite_t *sprite;
} env_obj_t;

typedef struct game {
  game_sprite_t *game_sprite;

  List_Node listeners;
  List_Node objects;
} game_t;

typedef struct listener {
  int arg_num;
  int act_num;
  void *listener;
} listener_t;

typedef struct single_listener {
  bool *(condition)(game_t, env_obj_t);
  void (*actions[])(game_t, env_obj_t);
} s_listener_t;

typedef struct double_listener {
  bool *(condition)(game_t, env_obj_t, env_obj_t);
  void (*actions[])(game_t, env_obj_t, env_obj_t);
} d_listener_t;


void add_object(game_t *game, void *object, int type);

void delete_object(game_t *game, void *object);

void add_single_listener(game_t *game, bool *condition(game_t*, env_obj_t*),
                         void (*actions[])(game_t*, env_obj_t*), int num_actions);

void add_double_listener(game_t *game, bool *condition(game_t*, env_obj_t*, env_obj_t*),
                         void (*actions[])(game_t*, env_obj_t*, env_obj_t*), int num_actions);

#endif