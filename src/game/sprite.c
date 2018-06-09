#include <math.h>

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
  s.dfwd = 0;
  s.dleft = 0;
  s.dright = 0;
  s.dbckwd = 0;
  s.rotation_speed = 7.5f;
  s.movement_speed = 12;

  return s;
}

void free_sprite(Sprite* sprite) { SDL_DestroyTexture(sprite->texture); }

void sprite_wasd_update_movement(Sprite* sprite, SDL_Scancode scancode,
                                 SDL_EventType eventtype) {
  switch (scancode) {
    case SDL_SCANCODE_W:
      sprite->dfwd = (eventtype == SDL_KEYDOWN);
      break;
    case SDL_SCANCODE_A:
      sprite->dleft = (eventtype == SDL_KEYDOWN);
      break;
    case SDL_SCANCODE_S:
      sprite->dbckwd = (eventtype == SDL_KEYDOWN);
      break;
    case SDL_SCANCODE_D:
      sprite->dright = (eventtype == SDL_KEYDOWN);
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
    sprite->angle = sprite->angle + sprite->rotation_speed > 360
                        ? sprite->angle + sprite->rotation_speed - 360
                        : sprite->angle + sprite->rotation_speed;
  }

  if (sprite->dfwd) {
    sprite->rectangle.x -=
        sin(to_radians(-sprite->angle)) * sprite->movement_speed;
    sprite->rectangle.y -=
        cos(to_radians(-sprite->angle)) * sprite->movement_speed;
  }
  if (sprite->dbckwd) {
    sprite->rectangle.x +=
        sin(to_radians(-sprite->angle)) * sprite->movement_speed;
    sprite->rectangle.y +=
        cos(to_radians(-sprite->angle)) * sprite->movement_speed;
  }
}

void sprite_keypress(Sprite* sprite, SDL_Event event) {
  SDL_Scancode scancode = event.key.keysym.scancode;
  SDL_EventType eventtype = event.type;
  sprite_wasd_update_movement(sprite, scancode, eventtype);
  sprite_propagate_movement(sprite);
}
