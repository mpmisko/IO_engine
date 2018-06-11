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

  // create sprite
  Sprite sprite = get_sprite(WINDOWWIDTH / 2, WINDOWHEIGHT / 2,
                             "resources/sprite1.png", game);

  int close_requested = 0;
  while (!close_requested) {
    SDL_Event event;
    // check if window should be closed
    while (!close_requested) {
      // check if some event occurred
      while (SDL_PollEvent(&event)) {
        switch (event.type) {
          case SDL_QUIT:
            close_requested = 1;
            break;
          case SDL_KEYUP:
          case SDL_KEYDOWN:
            sprite_keypress(&sprite, event);
            break;
          default:
            break;
        }
      }

      // propagate movement of sprite accordingly
      sprite_propagate_movement(&sprite);

      render_game(game, &sprite, 1);

      // introduce delay to maintain 60FPS
      SDL_Delay(1000 / 60);
    }
  }

  // Clean Up
  printf("cleaning up\n");
  free_sprite(&sprite);
  delete_game(game);
}
