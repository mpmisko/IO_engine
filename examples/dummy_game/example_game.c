#include "../../lib/io_lib.h"

/*
 * Structure definitions.
 */

enum types {PLAYER, SHOT, TREE};


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

/*
 * Structure initialisation and freeing.
 */

obj_sprite_t *player_sprite() {
  obj_sprite_t *p_sprite = malloc(sizeof(struct sprite_o));

  p_sprite->speed = 5;
  p_sprite->x = 10;
  p_sprite->y = 15;
}


void *create_player(game_t *game, int health, int power, int speed, int score, controls_t *control) {
  player_t *player = malloc(sizeof(struct player));

  if(!player) {
    return NULL;
  }

  player->health = health;
  player->controls = control;
  player->power = power;
  player->score = score;
  player->speed = speed;
  player->obj_sprite = player_sprite();

  add_object(game, player, PLAYER);
}

void destroy_player(player_t *player) {
  free(player->obj_sprite);
  free(player);
}

void *create_shot(game_t *game, int power, obj_sprite_t *sprite) {
  shot_t *shot = malloc(sizeof(struct shot));

  if(!shot) {
    return NULL;
  }

  shot->power = power;
  shot->obj_sprite = sprite;

  add_object(game, shot, SHOT);
}

void destroy_shot(shot_t *shot) {
  free(shot->obj_sprite);
  free(shot);
}

void *create_tree(game_t *game, int height, obj_sprite_t *sprite) {
  tree_t *tree = malloc(sizeof(struct tree));

  if (!tree) {
    return NULL;
  }

  tree->height = height;
  tree->obj_sprite = sprite;

  add_object(game, tree, TREE);
}

void shoot_action(game_t *game, env_obj_t *obj1) {
  player_t *p = (player_t*) obj1;
  obj_sprite_t *shot_sprite = malloc(sizeof(struct sprite_o));
  shot_sprite->x = p->obj_sprite->x;
  shot_sprite->y = p->obj_sprite->y;
  shot_sprite->speed = 100;

  create_shot(game, p->power, shot_sprite);
}

bool shoot_condition(game_t *game, env_obj_t *obj1) {
  if(obj1->type != PLAYER) {
    return false;
  }
  player_t *p = (player_t*) obj1;
  return (p->power > 10) && (is_clicked(obj1));
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
