#include "sprite.h"
#include "utils.h"

Sprite get_sprite(int x, int y, char* texture_path, SDL_Renderer* renderer,
                  SDL_Window* window) {
  SDL_Texture* texture = get_texture(texture_path, renderer, window);

  Sprite s;
  s.texture = texture;
  s.rectangle = get_rect_from_texture(texture);
  s.rectangle.x = x;
  s.rectangle.y = y;
  s.angle = 0;

  return s;
}

void free_sprite(Sprite* sprite) { SDL_DestroyTexture(sprite->texture); }

