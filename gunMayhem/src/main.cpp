#include <iostream>
#include "Game.h"
#include <thread>



int main() {

    Game game;
    bool isUpdated = true;
    std::mutex mut;
    std::condition_variable rend, upd;

    game.getGameWindow()->setActive(false);

    std::thread t1(&Game::render,&game ,&isUpdated, &mut,&rend, &upd);
    //std::thread t2(&Game::update,&game ,&isUpdated, &mut,&rend, &upd);

    game.update(&isUpdated, &mut,&rend, &upd);

    t1.join();
    //t2.join();

    return 0;
}
