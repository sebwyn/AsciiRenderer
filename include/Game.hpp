#pragma once

#include <memory>
#include <ncurses.h>

#include "World.hpp"
#include "Camera.hpp"
#include "Color.hpp"

class Game {
public:
    Game();

    void run();
    
    bool running = false;
private:
    void init();
    void mainloop();
    void cleanup();

    WINDOW* win;

    std::unique_ptr<World> world;
    std::unique_ptr<Camera> camera;

    std::unique_ptr<Color> whiteOnBlack;
};
