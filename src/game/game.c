#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../lib/io_lib.h"
#include "game.h"
#include "utils.h"

#ifndef APPLE
int snprintf(char* STR, size_t SIZE, const char* FORMAT, ...);
#endif

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
  memset(game->pressed_keys, 0, NUMKEYS * sizeof(short));

  game->listeners = get_new_list();
  game->objects = get_new_list();

  game->user_variables = NULL;

  return game;
}

void set_background(Game* game, char* path_to_texture) {
  game->background_texture = get_texture(path_to_texture, game->renderer);
  if (game->background_texture == NULL) {
    perror("Setting background texture failed\n");
  }
}

void render_game(Game* game) {
  if (game->background_texture != NULL) {
    SDL_RenderCopy(game->renderer, game->background_texture, NULL, NULL);
  } else {
    SDL_RenderClear(game->renderer);
  }

  List_Node* s_curr = game->objects;

  while (s_curr && s_curr->next) {
    s_curr = s_curr->next;
    Sprite* s = ((env_obj_t*)s_curr->data)->sprite;
    SDL_Point center = get_center(s->rectangle);
    if (SDL_RenderCopyEx(game->renderer, s->texture, NULL, &s->rectangle,
                         s->angle, &center, SDL_FLIP_NONE)) {
      perror("Unable to render sprite");
    }
  }

  Uint32 ticks_passed = SDL_GetTicks() - game->last_render_ticks + 1;
  game->last_render_ticks = SDL_GetTicks();
  game->fps = 1000 / ticks_passed;

  if (game->render_fps) {
    SDL_Color White = {255, 255, 255, 255};
    char* fps_str;
    fps_str = malloc(8);
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

void process_key_change(Game* game, SDL_Event event) {
  switch (event.key.keysym.scancode) {
    case SDL_SCANCODE_A:
      game->pressed_keys[A] = (event.type == SDL_KEYDOWN);
      break;
    case SDL_SCANCODE_B:
      game->pressed_keys[B] = (event.type == SDL_KEYDOWN);
      break;
    case SDL_SCANCODE_C:
      game->pressed_keys[C] = (event.type == SDL_KEYDOWN);
      break;
    case SDL_SCANCODE_D:
      game->pressed_keys[D] = (event.type == SDL_KEYDOWN);
      break;
    case SDL_SCANCODE_E:
      game->pressed_keys[E] = (event.type == SDL_KEYDOWN);
      break;
    case SDL_SCANCODE_F:
      game->pressed_keys[F] = (event.type == SDL_KEYDOWN);
      break;
    case SDL_SCANCODE_G:
      game->pressed_keys[G] = (event.type == SDL_KEYDOWN);
      break;
    case SDL_SCANCODE_H:
      game->pressed_keys[H] = (event.type == SDL_KEYDOWN);
      break;
    case SDL_SCANCODE_I:
      game->pressed_keys[I] = (event.type == SDL_KEYDOWN);
      break;
    case SDL_SCANCODE_J:
      game->pressed_keys[J] = (event.type == SDL_KEYDOWN);
      break;
    case SDL_SCANCODE_K:
      game->pressed_keys[K] = (event.type == SDL_KEYDOWN);
      break;
    case SDL_SCANCODE_L:
      game->pressed_keys[L] = (event.type == SDL_KEYDOWN);
      break;
    case SDL_SCANCODE_M:
      game->pressed_keys[M] = (event.type == SDL_KEYDOWN);
      break;
    case SDL_SCANCODE_N:
      game->pressed_keys[N] = (event.type == SDL_KEYDOWN);
      break;
    case SDL_SCANCODE_O:
      game->pressed_keys[O] = (event.type == SDL_KEYDOWN);
      break;
    case SDL_SCANCODE_P:
      game->pressed_keys[P] = (event.type == SDL_KEYDOWN);
      break;
    case SDL_SCANCODE_Q:
      game->pressed_keys[Q] = (event.type == SDL_KEYDOWN);
      break;
    case SDL_SCANCODE_R:
      game->pressed_keys[R] = (event.type == SDL_KEYDOWN);
      break;
    case SDL_SCANCODE_S:
      game->pressed_keys[S] = (event.type == SDL_KEYDOWN);
      break;
    case SDL_SCANCODE_T:
      game->pressed_keys[T] = (event.type == SDL_KEYDOWN);
      break;
    case SDL_SCANCODE_U:
      game->pressed_keys[U] = (event.type == SDL_KEYDOWN);
      break;
    case SDL_SCANCODE_V:
      game->pressed_keys[V] = (event.type == SDL_KEYDOWN);
      break;
    case SDL_SCANCODE_W:
      game->pressed_keys[W] = (event.type == SDL_KEYDOWN);
      break;
    case SDL_SCANCODE_X:
      game->pressed_keys[X] = (event.type == SDL_KEYDOWN);
      break;
    case SDL_SCANCODE_Y:
      game->pressed_keys[Y] = (event.type == SDL_KEYDOWN);
      break;
    case SDL_SCANCODE_Z:
      game->pressed_keys[Z] = (event.type == SDL_KEYDOWN);
      break;
    case SDL_SCANCODE_UP:
      game->pressed_keys[UP] = (event.type == SDL_KEYDOWN);
      break;
    case SDL_SCANCODE_DOWN:
      game->pressed_keys[DOWN] = (event.type == SDL_KEYDOWN);
      break;
    case SDL_SCANCODE_LEFT:
      game->pressed_keys[LEFT] = (event.type == SDL_KEYDOWN);
      break;
    case SDL_SCANCODE_RIGHT:
      game->pressed_keys[RIGHT] = (event.type == SDL_KEYDOWN);
      break;
    default:
      break;
  }
}

void process_events(Game* game) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        game->close_requested = 1;
        break;
      case SDL_KEYUP:
      case SDL_KEYDOWN:
        process_key_change(game, event);
        break;
      default:
        break;
    }
  }
}

void apply_single_listener(Game* game, s_listener_t* sl) {
  List_Node* o_curr = game->objects;

  while (o_curr && o_curr->next) {
    o_curr = o_curr->next;
    env_obj_t* e_obj = (env_obj_t*)o_curr->data;
    if ((*sl->condition)(game, e_obj)) {
      (*sl->action)(game, e_obj);
    }
  }
}

short is_pressed(Game* game, Keys key) { return game->pressed_keys[key]; }

void listen(Game* game) {
  List_Node* l_curr = game->listeners;

  while (l_curr && l_curr->next) {
    l_curr = l_curr->next;
    listener_t* l = (listener_t*)l_curr->data;

    if (l->arg_num == 1) {
      apply_single_listener(game, l->listener);
    }
  }
}

void delete_game(Game* game) {
  SDL_DestroyTexture(game->background_texture);
  SDL_DestroyRenderer(game->renderer);
  SDL_DestroyWindow(game->window);
  SDL_Quit();
  TTF_Quit();
  delete_list(game->listeners);
  delete_list(game->objects);
}
