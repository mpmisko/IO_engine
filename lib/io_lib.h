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
  game_sprite_t game_sprite;

  List_Node listeners;
  List_Node objects;
} game_t;

typedef struct listener {
  int arg_num;
  int cond_num;
  int act_num;
  void *listener;
} listener_t;

typedef struct single_listener {
  bool (*conditions[])(game_t, env_obj_t);
  void (*actions[])(game_t, env_obj_t);
} s_listener_t;

typedef struct double_listener {
  bool (*conditions[])(game_t, env_obj_t, env_obj_t);
  void (*actions[])(game_t, env_obj_t, env_obj_t);
} d_listener_t;


void initialise_game(game_t *game, env_obj_t *objects, listener_t *listener, int  num_listeners);

void add_object(game_t *game, void *object, int type);

void add_single_listener(game_t *game, bool (*conditions[])(game_t*, env_obj_t*),
                         int num_conds, void (*actions[])(game_t*, env_obj_t*), int num_actions);

void add_double_listener(game_t *game, bool (*conditions[])(game_t*, env_obj_t*, env_obj_t*),
                         int num_conds, void (*actions[])(game_t*, env_obj_t*, env_obj_t*), int num_actions);

env_obj_t get_environment_object(void *obj, int type);

#endif