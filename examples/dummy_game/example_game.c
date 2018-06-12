#include "../../lib/io_lib.h"

typedef struct player {
  int health;
  int score;
  int speed;
  int power;

  obj_sprite_t obj_sprite;
  controls_t controls;
} player_t;

typedef struct tree {
  int height;
  obj_sprite_t obj_sprite;
} tree_t;

typedef struct shot {
  int power;
  obj_sprite_t obj_sprite;
} shot_t;

typedef struct game {
  player_t *players;
  tree_t *trees;
  shot_t *shots;

  game_sprite_t game_sprite;
} game_t;

typedef struct events {

} events_t;

/*Actions and their corresponding conditions*/

void shoot_action(player_t *player, game_t *game) {
  //new_object("shot", player, game);
}

void decrease_health(player_t *player, int val) {
  player->health -= val;
}

void shot_action(player_t *player, shot_t *shot, game_t game) {
  decrease_health(player, 5);
  if(player->health <= 0) {
    //destroy_object(player);
  }
}

int tree_collision_cond1(player_t *p, tree_t *tree, game_t *game) {
  //return distance(p, tree) < 5;
}

int tree_collision_cond2(player_t *p, tree_t *tree, game_t *game) {
  return tree->height > 100;
}

void tree_collided_action(player_t *p, tree_t *tree, game_t *game) {
  decrease_health(p, tree->height/3);
}

void game_slowdown_action(player_t *p, tree_t *tree, game_t *game) {
  //game->speed -= 5;
}


