#include <iostream>
#include "Game.h"
#include <thread>



int main() {
    Game game;
    sf::Context context;

    bool isUpdated = true;
    std::mutex mut;
    std::condition_variable rend, upd;
    std::thread t1(&Game::render,&game ,&isUpdated, &mut,&rend, &upd);


    while (game.getWindowIsOpen()) {

        game.render(&isUpdated,&mut,&rend,&upd);
        game.update(&isUpdated,&mut,&rend,&upd);
    }

    t1.join();

    return 0;
}
