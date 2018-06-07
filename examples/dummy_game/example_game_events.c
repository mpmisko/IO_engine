#include "io_events_lib.h"

/*This file follows the game definition from the .json*/

/*Actions and their corresponding conditions*/

void shoot_action(Player *player, Game *game) {
  new_object("shot", player, game);
}

void decrease_health(Player *player, int val) {
  player->health -= val;
}

void shot_action(Player *player, Shot *shot, Game game) {
  decrease_health(player);
  if(player->health == 0) {
    destroy_object(player);
  }
}

int tree_collision_cond1(Player *p, Tree *tree, Game *game) {
  return distance(p, tree) < 5;
}

int tree_collision_cond2(Player *p, Tree *tree, Game *game) {
  return tree->height > 100;
}

void tree_collided_action(Player *p, Tree *tree, Game *game) {
  decrease_health(p, tree->height/3);
}

void game_slowdown_action(Player *p, Tree *tree, Game *game) {
  game->speed -= 5;
}


