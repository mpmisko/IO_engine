#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>

#include "../utils/linked_list/linked_list.h"

typedef enum { wasd = 0, arrows = 1, ijkl = 2, tfgh = 3, custom = 4 } Controls;

#define NUMKEYS 30

typedef enum {
  A,
  B,
  C,
  D,
  E,
  F,
  G,
  H,
  I,
  J,
  K,
  L,
  M,
  N,
  O,
  P,
  Q,
  R,
  S,
  T,
  U,
  V,
  W,
  X,
  Y,
  Z,
  UP,
  DOWN,
  LEFT,
  RIGHT
} Keys;

typedef struct sprite_ {
  SDL_Rect rectangle;
  SDL_Texture* texture;
  double angle;
  int dfwd;
  int dright;
  int dleft;
  int dbckwd;
  double rotation_speed;
  int movement_speed;
  Controls controls;
  void (*keypress_function)(struct sprite_*, SDL_Scancode, SDL_EventType);
} Sprite;

typedef struct game_ {
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Texture* background_texture;
  int fps;
  int render_fps;
  Uint32 last_render_ticks;
  int width;
  int height;
  int close_requested;
  // size of window

  List_Node* listeners;
  List_Node* objects;

  void* user_variables;
  short pressed_keys[NUMKEYS];
} Game;

// Game
Game* init_game();
void set_background(Game* game, char* path_to_texture);
void render_game(Game* game);
void process_events(Game* game);
void delete_game(Game* game);
short is_pressed(Game* game, Keys key);

// Sprites
Sprite* get_sprite(int x, int y, char* texture_path, Game* game);
void free_sprite(Sprite* sprite);
void sprite_keypress(Sprite* sprite, SDL_Event event);
void sprite_propagate_movement(Sprite* sprite);
void set_controls(Sprite* sprite, Controls controls,
                  void (*k_function)(Sprite*, SDL_Scancode, SDL_EventType));

#endif  // GAME_h
