#include <iostream>
#include "Game.h"

int main() {
    //setenv("DISPLAY", "192.168.0.104:7.0", true);
    Game game;

    while (game.getWindowIsOpen()) {
        game.update();
        game.render();
    }


    return 0;
}
