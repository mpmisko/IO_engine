#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>

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

Sprite get_sprite(int x, int y, char* texture_path, SDL_Renderer* renderer,
                  SDL_Window* window);
void free_sprite(Sprite* sprite);
void sprite_keypress(Sprite* sprite, SDL_Event event);

#endif  // SPRITE_H
