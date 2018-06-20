#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../lib/io_lib.h"
#include "../src/renderer_main.h"

#define BACKGROUND_PATH "resources/racer/map.png"
#define WINDOWWIDTH 1440
#define WINDOWHEIGHT 800

enum obj_types { empty, player, shot };

typedef struct {
  int hp;
  int dfwd;
  int dright;
  int dleft;
  int dbckwd;
  double rotation_speed;
  int movement_speed;
  int cooldown;
} Player;

typedef struct {
  int movement_speed;
  int shooter_id;
} Shot;


struct local_variables {
  int id1;
  int id2;
};

bool move_fwd_cond(Game* game, env_obj_t* obj) {
  struct local_variables lv = *(struct local_variables*)game->user_variables;
  if ((obj->id == lv.id1 && game->pressed_keys[W]) ||
      (obj->id == lv.id2 && game->pressed_keys[UP])) {
    return 1;
  } else {
    return 0;
  }
}

void move_fwd(Game* game, env_obj_t* obj) {
  obj->sprite->rectangle.x -= round(sin(to_radians(-obj->sprite->angle)) *
                                    ((Player*)obj->object)->movement_speed);
  obj->sprite->rectangle.y -= round(cos(to_radians(-obj->sprite->angle)) *
                                    ((Player*)obj->object)->movement_speed);
}

bool move_bckwd_cond(Game* game, env_obj_t* obj) {
  struct local_variables lv = *(struct local_variables*)game->user_variables;
  if ((obj->id == lv.id1 && game->pressed_keys[S]) ||
      (obj->id == lv.id2 && game->pressed_keys[DOWN])) {
    return 1;
  } else {
    return 0;
  }
}

void move_bckwd(Game* game, env_obj_t* obj) {
  obj->sprite->rectangle.x += round(sin(to_radians(-obj->sprite->angle)) *
                                    ((Player*)obj->object)->movement_speed);
  obj->sprite->rectangle.y += round(cos(to_radians(-obj->sprite->angle)) *
                                    ((Player*)obj->object)->movement_speed);
}

bool move_left_cond(Game* game, env_obj_t* obj) {
  struct local_variables lv = *(struct local_variables*)game->user_variables;
  if ((obj->id == lv.id1 && game->pressed_keys[A]) ||
      (obj->id == lv.id2 && game->pressed_keys[LEFT])) {
    return 1;
  } else {
    return 0;
  }
}

void move_left(Game* game, env_obj_t* obj) {
  obj->sprite->angle =
          obj->sprite->angle - ((Player*)obj->object)->rotation_speed < 0
          ? obj->sprite->angle - ((Player*)obj->object)->rotation_speed + 360
          : obj->sprite->angle - ((Player*)obj->object)->rotation_speed;
}

bool move_right_cond(Game* game, env_obj_t* obj) {
  struct local_variables lv = *(struct local_variables*)game->user_variables;
  if ((obj->id == lv.id1 && game->pressed_keys[D]) ||
      (obj->id == lv.id2 && game->pressed_keys[RIGHT])) {
    return 1;
  } else {
    return 0;
  }
}

void move_right(Game* game, env_obj_t* obj) {
  obj->sprite->angle =
          obj->sprite->angle + ((Player*)obj->object)->rotation_speed >= 360
          ? obj->sprite->angle + ((Player*)obj->object)->rotation_speed - 360
          : obj->sprite->angle + ((Player*)obj->object)->rotation_speed;
}

bool cooldown_cond(Game* game, env_obj_t* obj) {
  if(obj->type != player) {
    return false;
  }

  return ((Player *) obj->object)->cooldown > 0;
}

void cooldown_act(Game* game, env_obj_t* obj) {
  Player *pl = (Player *) obj->object;
  pl->cooldown--;
}

static double distance(env_obj_t* obj1, env_obj_t* obj2) {
  double square_difference_x = pow(obj1->sprite->rectangle.x - obj2->sprite->rectangle.x, 2);
  double square_difference_y = pow(obj1->sprite->rectangle.y - obj2->sprite->rectangle.y, 2);
  return sqrt(square_difference_x + square_difference_y);
}

bool shot_hit_cond(Game* game, env_obj_t* obj1, env_obj_t* obj2) {
  if((obj1->type != player) || (obj2->type != shot)) {
    return false;
  }

  if(((Shot *) obj2->object)->shooter_id == obj1->id) {
    return false;
  }

  return distance(obj1, obj2) < 30;
}

void shot_hit_act(Game* game, env_obj_t* obj1, env_obj_t* obj2) {
  delete_object(game, obj2);
  ((Player *) obj1->object)->hp -= 35;
}

bool shoot_condition(Game* game, env_obj_t* obj) {
  if(!(obj->type == player)) {
    return false;
  }
  struct local_variables lv = *(struct local_variables*)game->user_variables;

  return (((game->pressed_keys[O] && obj->id == lv.id1) ||
         ((game->pressed_keys[T] && obj->id == lv.id2))) && (((Player*) obj->object)->cooldown == 0));
}

void shoot_action(Game* game, env_obj_t* obj) {
  Shot s = {.movement_speed = 15, .shooter_id = obj->id};
  Sprite *shot_sprite = get_sprite(obj->sprite->rectangle.x, obj->sprite->rectangle.y,
                                   "resources/bullet.png", game);
  shot_sprite->angle = obj->sprite->angle;
  ((Player*) obj->object)->cooldown = 15;
  add_object(game, &s, sizeof(Shot), shot, shot_sprite);
}

bool shot_movement_cond(Game* game, env_obj_t* obj) {
  return obj->type == shot;
}

void shot_movement_act(Game* game, env_obj_t* obj) {
  Shot *shot_obj = (Shot*) obj->object;

  obj->sprite->rectangle.x -= round(sin(to_radians(-obj->sprite->angle)) *
                                    (shot_obj)->movement_speed);
  obj->sprite->rectangle.y -= round(cos(to_radians(-obj->sprite->angle)) *
                                    (shot_obj)->movement_speed);
}

bool kill_player_cond(Game* game, env_obj_t* obj) {
  if(!(obj->type == player)) {
    return false;
  }
  return ((Player *) obj->object)->hp <= 0;
}

void kill_player_act(Game* game, env_obj_t* obj) {
  delete_object(game, obj);
}

int main(void) {
  Game* game = init_game();  // create window

  set_background(game, BACKGROUND_PATH);

  // draw the image to the window
  // First draw texture to the copy of renderer and then swap the buffers

  struct local_variables lv;

  Player p1 = {100, 0, 0, 0, 0, 7.5, 12, 5};

  // create sprites
  lv.id1 = add_object(game, &p1, sizeof(Player), player,
                      get_sprite(100, 700,
                                 "resources/sprite1.png", game));

  Player p2 = {100, 0, 0, 0, 0, 7.5, 12, 5};
  lv.id2 = add_object(game, &p2, sizeof(Player), player,
                      get_sprite(150, 700,
                                 "resources/sprite2.png", game));

  add_single_listener(game, move_fwd_cond, move_fwd);
  add_single_listener(game, move_bckwd_cond, move_bckwd);
  add_single_listener(game, move_left_cond, move_left);
  add_single_listener(game, move_right_cond, move_right);
  add_single_listener(game, shoot_condition, shoot_action);
  add_single_listener(game, shot_movement_cond, shot_movement_act);
  add_single_listener(game, cooldown_cond, cooldown_act);
  add_single_listener(game, kill_player_cond, kill_player_act);
  add_double_listener(game, shot_hit_cond, shot_hit_act);

  game->user_variables = &lv;

  start_game(game);

  // Clean Up
  printf("cleaning up\n");
  delete_game(game);
}
