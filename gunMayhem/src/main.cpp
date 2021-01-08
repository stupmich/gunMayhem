#include "Game.h"
#include <thread>

Game game;
sf::Context context;

void render(bool * isUpdated, std::mutex *mut, std::condition_variable * render, std::condition_variable * update, RenderWindow *window) {
    while(game.getWindowIsOpen()) {
        window->setActive(true);
        std::unique_lock<std::mutex> lock(* mut);
        while (!(*isUpdated)) render->wait(lock);
        game.render();
        (*isUpdated) = false;
        update->notify_one();
    }
}

void update(bool * isUpdated, std::mutex *mut, std::condition_variable * render, std::condition_variable * update) {
    while(game.getWindowIsOpen()) {
        std::unique_lock<std::mutex> lock(*mut);
        while (*isUpdated) update->wait(lock);
        game.update();
        (*isUpdated) = true;
        render->notify_one();
    }
}

int main() {
    std::mutex mut;
    std::condition_variable rend, upd;
    bool isUpdated = false;
    game.getGameWindow()->setActive(false);
    std::thread t1(render,&isUpdated, &mut,&rend, &upd, game.getGameWindow());
    update(&isUpdated, &mut,&rend, &upd);
    t1.join();
    return 0;
}