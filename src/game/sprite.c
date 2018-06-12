#include <math.h>

#include "game.h"
#include "utils.h"

Sprite get_sprite(int x, int y, char* texture_path, Game* game) {
  SDL_Texture* texture = get_texture(texture_path, game->renderer);

  Sprite s;
  s.texture = texture;
  s.rectangle = get_rect_from_texture(texture);
  s.rectangle.x = x;
  s.rectangle.y = y;
  s.angle = 0;
  s.dfwd = 0;
  s.dleft = 0;
  s.dright = 0;
  s.dbckwd = 0;
  s.rotation_speed = 7.5f;
  s.movement_speed = 12;
  s.controls = custom;
  s.keypress_function = NULL;
  return s;
}

void free_sprite(Sprite* sprite) { SDL_DestroyTexture(sprite->texture); }

void sprite_wasd_update_movement(Sprite* sprite, SDL_Scancode scancode,
                                 SDL_EventType eventtype) {
  switch (scancode) {
    case SDL_SCANCODE_W:
      sprite->dfwd = (eventtype == SDL_KEYDOWN);
      // printf("W: %d\n", (eventtype == SDL_KEYDOWN));
      break;
    case SDL_SCANCODE_A:
      sprite->dleft = (eventtype == SDL_KEYDOWN);
      // printf("A: %d\n", (eventtype == SDL_KEYDOWN));
      break;
    case SDL_SCANCODE_S:
      sprite->dbckwd = (eventtype == SDL_KEYDOWN);
      // printf("S: %d\n", (eventtype == SDL_KEYDOWN));
      break;
    case SDL_SCANCODE_D:
      sprite->dright = (eventtype == SDL_KEYDOWN);
      // printf("D: %d\n", (eventtype == SDL_KEYDOWN));
      break;
    default:
      break;
  }
}

void sprite_arrows_update_movement(Sprite* sprite, SDL_Scancode scancode,
                                   SDL_EventType eventtype) {
  switch (scancode) {
    case SDL_SCANCODE_UP:
      sprite->dfwd = (eventtype == SDL_KEYDOWN);
      // printf("W: %d\n", (eventtype == SDL_KEYDOWN));
      break;
    case SDL_SCANCODE_LEFT:
      sprite->dleft = (eventtype == SDL_KEYDOWN);
      // printf("A: %d\n", (eventtype == SDL_KEYDOWN));
      break;
    case SDL_SCANCODE_DOWN:
      sprite->dbckwd = (eventtype == SDL_KEYDOWN);
      // printf("S: %d\n", (eventtype == SDL_KEYDOWN));
      break;
    case SDL_SCANCODE_RIGHT:
      sprite->dright = (eventtype == SDL_KEYDOWN);
      // printf("D: %d\n", (eventtype == SDL_KEYDOWN));
      break;
    default:
      break;
  }
}

void sprite_ijkl_update_movement(Sprite* sprite, SDL_Scancode scancode,
                                 SDL_EventType eventtype) {
  switch (scancode) {
    case SDL_SCANCODE_I:
      sprite->dfwd = (eventtype == SDL_KEYDOWN);
      // printf("W: %d\n", (eventtype == SDL_KEYDOWN));
      break;
    case SDL_SCANCODE_J:
      sprite->dleft = (eventtype == SDL_KEYDOWN);
      // printf("A: %d\n", (eventtype == SDL_KEYDOWN));
      break;
    case SDL_SCANCODE_K:
      sprite->dbckwd = (eventtype == SDL_KEYDOWN);
      // printf("S: %d\n", (eventtype == SDL_KEYDOWN));
      break;
    case SDL_SCANCODE_L:
      sprite->dright = (eventtype == SDL_KEYDOWN);
      // printf("D: %d\n", (eventtype == SDL_KEYDOWN));
      break;
    default:
      break;
  }
}

void sprite_tfgh_update_movement(Sprite* sprite, SDL_Scancode scancode,
                                 SDL_EventType eventtype) {
  switch (scancode) {
    case SDL_SCANCODE_T:
      sprite->dfwd = (eventtype == SDL_KEYDOWN);
      // printf("W: %d\n", (eventtype == SDL_KEYDOWN));
      break;
    case SDL_SCANCODE_F:
      sprite->dleft = (eventtype == SDL_KEYDOWN);
      // printf("A: %d\n", (eventtype == SDL_KEYDOWN));
      break;
    case SDL_SCANCODE_G:
      sprite->dbckwd = (eventtype == SDL_KEYDOWN);
      // printf("S: %d\n", (eventtype == SDL_KEYDOWN));
      break;
    case SDL_SCANCODE_H:
      sprite->dright = (eventtype == SDL_KEYDOWN);
      // printf("D: %d\n", (eventtype == SDL_KEYDOWN));
      break;
    default:
      break;
  }
}

void sprite_propagate_movement(Sprite* sprite) {
  if (sprite->dleft) {
    sprite->angle = sprite->angle - sprite->rotation_speed < 0
                        ? sprite->angle - sprite->rotation_speed + 360
                        : sprite->angle - sprite->rotation_speed;
  }
  if (sprite->dright) {
    sprite->angle = sprite->angle + sprite->rotation_speed >= 360
                        ? sprite->angle + sprite->rotation_speed - 360
                        : sprite->angle + sprite->rotation_speed;
  }

  if (sprite->dfwd) {
    sprite->rectangle.x -=
        round(sin(to_radians(-sprite->angle)) * sprite->movement_speed);
    sprite->rectangle.y -=
        round(cos(to_radians(-sprite->angle)) * sprite->movement_speed);
  }
  if (sprite->dbckwd) {
    sprite->rectangle.x +=
        round(sin(to_radians(-sprite->angle)) * sprite->movement_speed);
    sprite->rectangle.y +=
        round(cos(to_radians(-sprite->angle)) * sprite->movement_speed);
  }
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
  static void (*key_functions[])(Sprite*, SDL_Scancode, SDL_EventType) = {
      sprite_wasd_update_movement, sprite_arrows_update_movement,
      sprite_ijkl_update_movement, sprite_tfgh_update_movement};
  sprite->controls = controls;
  if (sprite->controls == custom) {
    sprite->keypress_function = k_function;
  } else {
    sprite->keypress_function = key_functions[sprite->controls];
  }
}
