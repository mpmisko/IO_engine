#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "../src/game/game.h"
#include "../src/utils/linked_list/linked_list.h"

#ifndef IO_LIB_H
#define IO_LIB_H

#define SINGLE_ARG_LISTENER 1
#define DOUBLE_ARG_LISTENER 2

typedef enum {WASD, arrow_key_mode, IJKL} control_mode_t;

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

typedef struct environment_object {
  int id;
  int type;
  void *object;
  Sprite *sprite;
} env_obj_t;

typedef struct listener {
  int arg_num;
  void *listener;
} listener_t;

typedef struct single_listener {
  bool (*condition)(Game*, env_obj_t*);
  void (*actions)(Game*, env_obj_t*);
} s_listener_t;

typedef struct double_listener {
  bool (*condition)(Game*, env_obj_t*, env_obj_t*);
  void (*actions)(Game*, env_obj_t*, env_obj_t*);
} d_listener_t;


int add_object(Game *game, void *object, int type, Sprite *sprite);

void delete_object(Game *game, env_obj_t *object);

void add_single_listener(Game *game, bool (*condition)(Game*, env_obj_t*),
                         void (*actions)(Game*, env_obj_t*));

void add_double_listener(Game *game, bool (*condition)(Game*, env_obj_t*, env_obj_t*),
                         void (*actions)(Game*, env_obj_t*, env_obj_t*));

#endif
