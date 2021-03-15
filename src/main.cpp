#include "game.h"

int main()
{
    // Init random seed
    srand(time(NULL));

    // Initialize game.
    cb::Game game;

    // Game loop.
    while (game.isOpen())
    {
        // Update state.
        game.update();

        // Detect collisions.
        game.detectCollisions();

        // Draw.
        game.render();
    }




    return 1;
}