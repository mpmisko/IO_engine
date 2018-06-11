#include "game.h"
#include "utils.h"

#define WINDOWTITLE "Game Engine: Othello"
#define WINDOWWIDTH 1440
#define WINDOWHEIGHT 800

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

Game* init_game() {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER)) {
    perror("SDL_Init Failed");
    exit(1);
  }

  Game* game = malloc(sizeof(Game));

  game->window = init_window();
  game->renderer = init_renderer(game->window);
  game->background_texture = NULL;

  return game;
}

void set_background(Game* game, char* path_to_texture) {
  game->background_texture = get_texture(path_to_texture, game->renderer);
  if (game->background_texture == NULL) {
    perror("Setting background texture failed\n");
  }
}

void render_game(Game* game, Sprite* sprites, int num_sprites) {
  if (game->background_texture != NULL) {
    SDL_RenderCopy(game->renderer, game->background_texture, NULL, NULL);
  } else {
    SDL_RenderClear(game->renderer);
  }

  for (int i = 0; i < num_sprites; ++i) {
    SDL_Point center = get_center(sprites[i].rectangle);
    if (SDL_RenderCopyEx(game->renderer, sprites[i].texture, NULL,
                         &sprites[i].rectangle, sprites[i].angle, &center,
                         SDL_FLIP_NONE)) {
      perror("Unable to render sprite");
    }
  }

  SDL_RenderPresent(game->renderer);
}

void delete_game(Game* game) {
  SDL_DestroyTexture(game->background_texture);
  SDL_DestroyRenderer(game->renderer);
  SDL_DestroyWindow(game->window);
  SDL_Quit();
}
