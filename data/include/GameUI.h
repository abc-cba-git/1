#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"

class GameUI {
public:
    GameUI();
    void run();

private:
    void handleEvents();
    void update();
    void render();
    void handleClick(int x, int y);

    sf::RenderWindow window_;
    Game game_;
    Unit* selectedUnit_;
};