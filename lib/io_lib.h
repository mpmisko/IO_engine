#include <stdbool.h>

#ifndef IO_LIB_H
#define IO_LIB_H

typedef enum {WASD, arrow_key_mode, IJKL} control_mode_t;

typedef struct controls {
  bool shooting;
  control_mode_t control_mode;
} controls_t;

typedef struct sprite {
  int x;
  int y;
  int speed;
} obj_sprite_t;

typedef struct sprite {
  int x;
  int y;
  int speed;
} game_sprite_t;

#endif