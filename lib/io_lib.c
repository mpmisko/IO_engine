#include "io_lib.h"

int add_object(Game *game, void *object, int type, Sprite *sprite) {
  static int id = 0;
  env_obj_t *env_obj = malloc(sizeof(struct environment_object));
  env_obj->type = type;
  env_obj->object = object;
  env_obj->sprite = sprite;
  env_obj->id = id;
  append(game->objects, env_obj, sizeof(struct environment_object));
  return id++;
}

void delete_object(Game *game, env_obj_t *object) {
  delete_node(game->objects, object);
  free_sprite(object->sprite);
}

void add_single_listener(Game *game, bool (*condition)(Game *, env_obj_t *),
                         void (*actions)(Game *, env_obj_t *)) {
  listener_t *lnr = malloc(sizeof(struct listener));
  lnr->arg_num = SINGLE_ARG_LISTENER;

  s_listener_t *sin_lnr = malloc(sizeof(struct single_listener));
  sin_lnr->condition = condition;
  sin_lnr->actions = actions;

  lnr->listener = sin_lnr;
  append(game->listeners, lnr, sizeof(struct listener));
}

void add_double_listener(Game *game,
                         bool (*condition)(Game *, env_obj_t *, env_obj_t *),
                         void (*actions)(Game *, env_obj_t *, env_obj_t *)) {
  listener_t *lnr = malloc(sizeof(struct listener));
  lnr->arg_num = DOUBLE_ARG_LISTENER;

  d_listener_t *doub_lnr = malloc(sizeof(struct double_listener));
  doub_lnr->condition = condition;
  doub_lnr->actions = actions;

  lnr->listener = doub_lnr;
  append(game->listeners, lnr, sizeof(struct listener));
}
