#include <math.h>
#include <stdio.h>
#include "game/game.h"
#include "game/utils.h"

#define BACKGROUND_PATH "resources/background.jpg"
#define WINDOWWIDTH 1440
#define WINDOWHEIGHT 800

int main(void) {
  Game* game = init_game();  // create window

  set_background(game, BACKGROUND_PATH);

  // draw the image to the window
  // First draw texture to the copy of renderer and then swap the buffers

  // create sprites
  Sprite sprites[] = {get_sprite(WINDOWWIDTH / 3, WINDOWHEIGHT / 2,
                                 "resources/sprite1.png", game),
                      get_sprite(2 * WINDOWWIDTH / 3, WINDOWHEIGHT / 2,
                                 "resources/sprite2.png", game)};
  set_controls(&sprites[0], wasd, NULL);
  set_controls(&sprites[1], arrows, NULL);

  while (!game->close_requested) {
    // process events
    process_events(game, sprites, 2);

    // propagate movement of sprite accordingly
    sprite_propagate_movement(sprites);
    sprite_propagate_movement(sprites + 1);

    render_game(game, sprites, 2);
  }

  // Clean Up
  printf("cleaning up\n");
  free_sprite(&sprites[0]);
  free_sprite(&sprites[1]);
  delete_game(game);
}
