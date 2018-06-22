#include <math.h>

#include "game.h"
#include "utils.h"

Sprite* get_sprite(int x, int y, char* texture_path, Game* game) {
  SDL_Texture* texture = get_texture(texture_path, game->renderer);

  Sprite* s = malloc(sizeof(Sprite));
  s->texture = texture;
  s->rectangle = get_rect_from_texture(texture);
  s->rectangle.x = x;
  s->rectangle.y = y;
  s->angle = 0;
  return s;
}

void free_sprite(Sprite* sprite) {
  SDL_DestroyTexture(sprite->texture);
  free(sprite);
}
