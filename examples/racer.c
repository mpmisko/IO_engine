#include <stdio.h>
#include "../lib/io_lib.h"
#include "../src/renderer_main.h"

#define BACKGROUND_PATH "resources/background.jpg"
#define WINDOWWIDTH 1440
#define WINDOWHEIGHT 800

enum obj_types { empty, player };

typedef struct {
  int hp;
} Player;

int main(void) {
  Game* game = init_game();  // create window

  set_background(game, BACKGROUND_PATH);

  // draw the image to the window
  // First draw texture to the copy of renderer and then swap the buffers

  Player p1 = {100};

  // create sprites
  add_object(game, &p1, empty,
             get_sprite(WINDOWWIDTH / 3, WINDOWHEIGHT / 2,
                        "resources/sprite1.png", game));

  Player p2 = {100};
  add_object(game, &p2, empty,
             get_sprite(2 * WINDOWWIDTH / 3, WINDOWHEIGHT / 2,
                        "resources/sprite2.png", game));

  start_game(game);

  // Clean Up
  printf("cleaning up\n");
  delete_game(game);
}
