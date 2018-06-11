#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

typedef enum { wasd, arrows, ijkl, tfgh } controls;

typedef struct {
  SDL_Rect rectangle;
  SDL_Texture* texture;
  double angle;
  int dfwd;
  int dright;
  int dleft;
  int dbckwd;
  double rotation_speed;
  int movement_speed;
} Sprite;

typedef struct game_ {
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Texture* background_texture;
  // size of window
  // FPS
} Game;

// Game
Game* init_game();
void set_background(Game* game, char* path_to_texture);
void render_game(Game* game, Sprite* sprites, int num_sprites);
void delete_game(Game* game);

// Sprites
Sprite get_sprite(int x, int y, char* texture_path, Game* game);
void free_sprite(Sprite* sprite);
void sprite_keypress(Sprite* sprite, SDL_Event event);
void sprite_propagate_movement(Sprite* sprite);

#endif  // GAME_h
