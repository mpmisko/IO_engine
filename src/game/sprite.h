#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>

typedef struct {
  SDL_Rect rectangle;
  SDL_Texture* texture;
  double angle;
} Sprite;

Sprite get_sprite(int x, int y, char* texture_path, SDL_Renderer* renderer,
                  SDL_Window* window);
void free_sprite(Sprite* sprite);

#endif  // SPRITE_H
