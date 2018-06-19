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
  s->rotation_speed = 7.5f;
  s->movement_speed = 12;
  s->controls = custom;
  s->keypress_function = NULL;
  return s;
}

void free_sprite(Sprite* sprite) {
  SDL_DestroyTexture(sprite->texture);
  free(sprite);
}

void sprite_keypress(Sprite* sprite, SDL_Event event) {
  SDL_Scancode scancode = event.key.keysym.scancode;
  SDL_EventType eventtype = event.type;
  if (sprite->keypress_function != NULL) {
    sprite->keypress_function(sprite, scancode, eventtype);
  } else {
    printf("No sprite keypress_function defined\n");
  }
}

void set_controls(Sprite* sprite, Controls controls,
                  void (*k_function)(Sprite*, SDL_Scancode, SDL_EventType)) {
  //static void (*key_functions[])(Sprite*, SDL_Scancode, SDL_EventType) = {
      //sprite_wasd_update_movement, sprite_arrows_update_movement,
      //sprite_ijkl_update_movement, sprite_tfgh_update_movement};
  sprite->controls = controls;
  if (sprite->controls == custom) {
    sprite->keypress_function = k_function;
  } else {
    //sprite->keypress_function = key_functions[sprite->controls];
  }
}
