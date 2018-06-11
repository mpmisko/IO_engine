#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <math.h>
#include <stdio.h>

#include "game/sprite.h"
#include "game/utils.h"

#define WINDOWTITLE "Game Engine: Othello"
#define WINDOWWIDTH 1440
#define WINDOWHEIGHT 800
#define WAIT 5000
#define BACKGROUND_PATH "resources/background.jpg"

// SDL must be initialised
SDL_Window* init_window() {
  SDL_Window* window =
      SDL_CreateWindow(WINDOWTITLE, SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, WINDOWWIDTH, WINDOWHEIGHT, 0);

  if (!window) {
    perror("SDL_CreateWindow failed\n");
    SDL_Quit();
    exit(1);
  }

  return window;
}

// SDL must be initialised
SDL_Renderer* init_renderer(SDL_Window* window) {
  SDL_Renderer* renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!renderer) {
    perror("SDL_Create_Renderer failed\n");
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(1);
  }

  return renderer;
}

int main(void) {
  // Initialise sdl video and timer
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER)) {
    perror("SDL_Init Failed");
    return 1;
  }

  // create window
  SDL_Window* window = init_window();

  // initialize the renderer
  SDL_Renderer* renderer = init_renderer(window);

  // get backfround texture
  SDL_Texture* background_texture =
      get_texture(BACKGROUND_PATH, renderer, window);

  // clear the window
  SDL_RenderClear(renderer);

  // draw the image to the window
  // First draw texture to the copy of renderer and then swap the buffers
  SDL_RenderCopy(renderer, background_texture, NULL, NULL);
  SDL_RenderPresent(renderer);

  // create sprite
  Sprite sprite = get_sprite(WINDOWWIDTH / 2, WINDOWHEIGHT / 2,
                             "resources/sprite1.png", renderer, window);

  int close_requested = 0;
  while (!close_requested) {
    SDL_Event event;
    // check if window should be closed
    while (!close_requested) {

      //check if some event occurred
      while (SDL_PollEvent(&event)) {
        switch (event.type) {
          case SDL_QUIT:
            close_requested = 1;
            break;
          case SDL_KEYUP:
          case SDL_KEYDOWN:
            sprite_keypress(&sprite, event);
            break;
          default:
            break;
        }
      }

      // propagate movement of sprite accordingly
      sprite_propagate_movement(&sprite);

      // render background and sprite
      SDL_Point center = get_center(sprite.rectangle);
      SDL_RenderCopy(renderer, background_texture, NULL, NULL);
      if (SDL_RenderCopyEx(renderer, sprite.texture, NULL, &sprite.rectangle,
                           sprite.angle, &center, SDL_FLIP_NONE)) {
        clean_up(renderer, window);
        printf("error rendering texture: %s\n", SDL_GetError());
        return 1;
      }
      
      // switch rendering buffers
      SDL_RenderPresent(renderer);

      printf("angle: %f\n", sprite.angle);

      // introduce delay to maintain 60FPS
      SDL_Delay(1000 / 60);
    }
  }

  // Clean Up
  printf("cleaning up\n");
  free_sprite(&sprite);
  SDL_DestroyTexture(background_texture);
  clean_up(renderer, window);
}
