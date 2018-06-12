#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    printf("SDL_Init Failed: %s\n", SDL_GetError());
    exit(1);
  }

  if (TTF_Init()) {
    printf("TTF_Init Failed: %s\n", TTF_GetError());
    exit(1);
  }

  Game* game = malloc(sizeof(Game));

  game->window = init_window();
  game->renderer = init_renderer(game->window);
  game->background_texture = NULL;
  game->fps = 0;  // default value
  game->last_render_ticks = 0;
  game->render_fps = 1;
  game->width = WINDOWWIDTH;
  game->height = WINDOWHEIGHT;
  game->close_requested = 0;

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

  Uint32 ticks_passed = SDL_GetTicks() - game->last_render_ticks + 1;
  game->last_render_ticks = SDL_GetTicks();
  game->fps = 1000 / ticks_passed;

  if (game->render_fps) {
    SDL_Color White = {255, 255, 255, 255};
    char fps_str[8];
    snprintf(fps_str, 7, "%d fps", game->fps);
    SDL_Texture* fps_texture = get_text_texture(fps_str, White, game->renderer);
    SDL_Rect texture_rect;
    texture_rect.h = 40;
    texture_rect.w = 60;
    texture_rect.x = game->width - texture_rect.w;
    texture_rect.y = 0;
    SDL_RenderCopy(game->renderer, fps_texture, NULL, &texture_rect);
    SDL_DestroyTexture(fps_texture);
  }

  SDL_RenderPresent(game->renderer);
}

void process_events(Game* game, Sprite* sprites, int num_sprites) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        game->close_requested = 1;
        break;
      case SDL_KEYUP:
      case SDL_KEYDOWN:
        for (int i = 0; i < num_sprites; i++) {
          sprite_keypress(sprites + i, event);
        }
        break;
      default:
        break;
    }
  }
}

void delete_game(Game* game) {
  SDL_DestroyTexture(game->background_texture);
  SDL_DestroyRenderer(game->renderer);
  SDL_DestroyWindow(game->window);
  SDL_Quit();
  TTF_Quit();
}
