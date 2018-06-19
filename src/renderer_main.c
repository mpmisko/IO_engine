#include "renderer_main.h"

int start_game(Game* game) {
  while (!game->close_requested) {
    // process events
    process_events(game);

    // propagate movement of sprite accordingly
    // sprite_propagate_movement(sprites);
    // sprite_propagate_movement(sprites + 1);
    listen(game);

    render_game(game);
  }

  return 0;
}
