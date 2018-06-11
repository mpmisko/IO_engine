#include <math.h>

#include "utils.h"

#define PI acos(-1.0) 

SDL_Texture* get_texture(const char* path, SDL_Renderer * renderer) {
  SDL_Surface* surface = IMG_Load(path);
  if (!surface) {
    perror("IMG_Load Failed\n");
    return NULL;
  }

  // if (SDL_SetColorKey(surface, SDL_TRUE,
  //                      SDL_MapRGB(surface->format, 255, 255, 255))) {
  //   perror("SetColorKey Failed\n");
  //   clean_up(renderer, window);
  //   exit(1);
  // }

  // load the image data into the graphics hardware's memory
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  if (!texture) {
    perror("CreateTextureFromSurface Failed\n");
    return NULL;
  }

  return texture;

  // SDL_Texture * texture = IMG_LoadTexture(renderer, path);
  // if(texture) {
  //  return texture;
  // } else {
  //  perror("IMG_LoadTexture Failed");
  //  clean_up(renderer, window);
  //  exit(1);
  // }
}

SDL_Rect get_rect_from_texture(SDL_Texture* texture) {
  SDL_Rect rect;
  SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
  return rect;
}

SDL_Point get_center(SDL_Rect rectangle) {
  SDL_Point center = {rectangle.w / 2,
                      rectangle.h / 2};
  return center;
}

double to_degrees(double radians) {
      return radians * (180.0f / PI);
}

double to_radians(double degrees) {
  return (degrees * PI) / 180.0f;
}
