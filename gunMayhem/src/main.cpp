#include <iostream>
#include <SFML/Network.hpp>
#include "Game.h"

int main() {
    Game game;





//branch
    while (game.getWindowIsOpen()) {
        game.update();
        game.render();
    }


    return 0;
}
