#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <math.h>
#include <stdio.h>

#define WINDOWTITLE "Game Engine: Othello"
#define WINDOWWIDTH 1440
#define WINDOWHEIGHT 800
#define WAIT 5000
#define BACKGROUND_PATH "resources/background.jpg"

void clean_up(SDL_Renderer* renderer, SDL_Window* window) {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

SDL_Texture* get_texture(const char* path, SDL_Renderer* renderer,
                         SDL_Window* window) {
  SDL_Surface* background_surface = IMG_Load(path);
  if (!background_surface) {
    perror("IMG_Load Failed\n");
    clean_up(renderer, window);
    exit(1);
  }

  // load the image data into the graphics hardware's memory
  SDL_Texture* texture =
      SDL_CreateTextureFromSurface(renderer, background_surface);
  SDL_FreeSurface(background_surface);
  if (!texture) {
    perror("CreateTextureFromSurface Failed\n");
    clean_up(renderer, window);
    exit(1);
  }

  return texture;
}

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

SDL_Rect get_rect_from_texture(SDL_Texture* texture) {
  SDL_Rect rect;
  SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
  return rect;
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
  SDL_Texture* sprite_texture =
      get_texture("resources/rectangle.png", renderer, window);
  SDL_Rect sprite_rect = get_rect_from_texture(sprite_texture);

  sprite_rect.x = 0;
  sprite_rect.y = WINDOWHEIGHT / 2;
  int direction = 1;
  int close_requested = 0;
  while (!close_requested) {
    SDL_Event event;
    // check if window should be closed
    while ((!close_requested) &&
           (direction == 1 ? sprite_rect.x + sprite_rect.w < WINDOWWIDTH
                           : sprite_rect.x > 0)) {
      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          close_requested = 1;
        }
      }
      sprite_rect.x =
          sprite_rect.x +
          direction *
              (WINDOWWIDTH / 2 -
               abs(WINDOWWIDTH / 2 - (sprite_rect.x + sprite_rect.w / 2))) /
              20 +
          direction;
      SDL_RenderCopy(renderer, background_texture, NULL, NULL);
      SDL_RenderCopy(renderer, sprite_texture, NULL, &sprite_rect);
      SDL_RenderPresent(renderer);

      SDL_Delay(1000 / 60);
    }
    direction *= -1;
  }

  // Clean Up
  clean_up(renderer, window);
}
