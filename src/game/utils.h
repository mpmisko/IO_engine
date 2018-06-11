#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Texture* get_texture(const char* path, SDL_Renderer * renderer);
SDL_Rect get_rect_from_texture(SDL_Texture* texture);
SDL_Point get_center(SDL_Rect rectangle);
double to_degrees(double radians);
double to_radians(double degrees);

#endif // UTILS_H
