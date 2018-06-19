#include "../../lib/io_lib.h"

/*
 * Structure definitions.
 */

//definition comes later
static obj_sprite_t *shot_sprite;
static obj_sprite_t *player_sprite;


typedef struct player {
  int health;
  int score;
  int speed;
  int power;

  obj_sprite_t *obj_sprite;
  controls_t *controls;
} player_t;

typedef struct tree {
  int height;
  obj_sprite_t *obj_sprite;
} tree_t;

typedef struct shot {
  int power;
  obj_sprite_t *obj_sprite;
} shot_t;

typedef struct shoot_listener {
  bool (*conditions[])(player_t*);
  void (*actions[])(player_t *player, game_t *game);
} shoot_listener_t;

typedef struct shot_listener {
  bool (*conditions[])(player_t *player, shot_t *shot);
  void (*actions[])(player_t *player, shot_t *shot);
} shot_listener_t;

/*
 * Structure initialisation and freeing.
 */

player_t *create_player(int health, int power, int speed, int score, controls_t *control, obj_sprite_t *sprite) {
  player_t *player = malloc(sizeof(struct player));

  if(!player) {
    return NULL;
  }

  player->health = health;
  player->controls = control;
  player->power = power;
  player->score = score;
  player->speed = speed;
  player->obj_sprite = sprite;

  return player;
}

void destroy_player(player_t *player) {
  //remove sprite only if it is different from the global sprite
  if(player->obj_sprite != player_sprite) {
    free(player->obj_sprite);
  }
  free(player);
}

void destroy_shot(shot_t *shot) {
  //remove sprite only if it is different from the global sprite
  if(shot->obj_sprite != shot_sprite) {
    free(shot->obj_sprite);
  }
  free(shot);
}

tree_t *create_tree(int height, obj_sprite_t *sprite) {
  tree_t *tree = malloc(sizeof(struct tree));

  if(!tree) {
    return NULL;
  }

  tree->height = height;
  tree->obj_sprite = sprite;

  return tree;
}

shot_t *create_shot(int power, obj_sprite_t *sprite) {
  shot_t *shot = malloc(sizeof(struct shot));

  if(!shot) {
    return NULL;
  }

  shot->power = power;
  shot->obj_sprite = sprite;

  return shot;
}

void shoot_action(player_t *player, game_t *game) {
  shot_t *shot = create_shot(player->power, shot_sprite);
  list_append(game->environment_objects, shot);
}

bool shoot_condition(player_t *player) {
  return player->health > 5;
}

shoot_listener_t *create_shoot_event() {
  shoot_listener_t *event = malloc(sizeof(shoot_listener_t));

  if(!event) {
    return NULL;
  }

  event->actions = {&shoot_action};
  event->conditions = {&shoot_condition};

  return event;
}

void shot_action(player_t *player, shot_t *shot) {
  player->health -= shot->power;
  if(player->health <= 0) {
    destroy_player(player);
  }
  destroy_shot(shot);
}

long distance(obj_sprite_t *obj1, obj_sprite_t *obj2) {
  return lroundl(sqrt(pow(obj1->x - obj2->x, 2) + pow(obj1->y - obj2->y, 2)));
}

bool shot_condition(player_t *player, shot_t *shot) {
  return distance(player->obj_sprite, shot->obj_sprite) < 5;
}

shot_listener_t *create_shot_event() {
  shot_listener_t *event = malloc(sizeof(shot_listener_t));

  if(!event) {
    return NULL;
  }

  event->actions = {&shot_action};
  event->conditions = {&shot_condition};

  return event;
}

