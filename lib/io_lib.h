#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <linked_list.h>

#ifndef IO_LIB_H
#define IO_LIB_H

typedef enum {WASD, arrow_key_mode, IJKL} control_mode_t;

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

typedef struct game {
  game_sprite_t game_sprite;

  llist events;
  llist environment_objects;
} game_t;

#endif