#include "io_lib.h"

void initialise_game(game_t *game, env_obj_t *objects, int num_objects) {
  for (int i = 0; i < num_objects; ++i) {
    add_object(game, objects);
  }
}

void add_object(game_t *game, void *object, int type) {
  env_obj_t *env_obj = malloc(sizeof(struct environment_object));
  env_obj->type = type;
  env_obj->object = object;
  append(game->objects, env_obj);
}

void add_single_listener(game_t *game, bool (*condition)(game_t*, env_obj_t*),
void (*actions[])(game_t*, env_obj_t*), int num_actions) {
  listener_t *lnr = malloc(sizeof(struct listener));
  lnr->arg_num = SINGLE_ARG_LISTENER;
  lnr->act_num = num_actions;

  s_listener_t *sin_lnr = malloc(sizeof(struct single_listener));
  sin_lnr->condition = condition;
  sin_lnr->actions = actions;

  lnr->listener = sin_lnr;
  append(game->listeners, lnr);
}

void add_double_listener(game_t game, bool (*condition)(game_t*, env_obj_t*, env_obj_t*),
                         int num_conds, void (*actions[])(game_t*, env_obj_t*, env_obj_t*), int num_actions) {
  listener_t *lnr = malloc(sizeof(struct listener));
  lnr->arg_num = DOUBLE_ARG_LISTENER;
  lnr->act_num = num_actions;

  d_listener_t *doub_lnr = malloc(sizeof(struct double_listener));
  doub_lnr->condition = condition;
  doub_lnr->actions = actions;

  lnr->listener = doub_lnr;
  append(game->listeners, lnr);
}