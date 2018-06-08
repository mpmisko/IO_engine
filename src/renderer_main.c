#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>

#define WINDOWTITLE "Game Engine: Othello"
#define WINDOWWIDTH 660
#define WINDOWHEIGHT 294
#define WAIT 5000
#define BACKGROUND_PATH "resources/othello.png"

void clean_up(SDL_Renderer* renderer, SDL_Window* window) {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

SDL_Texture* get_background_texture(SDL_Renderer* renderer,
                                    SDL_Window* window) {
  SDL_Surface* background_surface = IMG_Load(BACKGROUND_PATH);
  if (!background_surface) {
    perror("IMG_Load Failed\n");
    clean_up(renderer, window);
    exit(1);
  }

  // load the image data into the graphics hardware's memory
  SDL_Texture* background_texture =
      SDL_CreateTextureFromSurface(renderer, background_surface);
  SDL_FreeSurface(background_surface);
  if (!background_texture) {
    perror("CreateTextureFromSurface Failed\n");
    clean_up(renderer, window);
    exit(1);
  }

  return background_texture;
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
  SDL_Renderer* renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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
  SDL_Texture* background_texture = get_background_texture(renderer, window);

  // clear the window
  SDL_RenderClear(renderer);

  // draw the image to the window
  // First draw texture to the copy of renderer and then swap the buffers
  SDL_RenderCopy(renderer, background_texture, NULL, NULL);
  SDL_RenderPresent(renderer);

  // wait a few seconds
  SDL_Delay(WAIT);

  // Clean Up
  clean_up(renderer, window);
}
