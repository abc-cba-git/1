#include "GameUI.h"

GameUI::GameUI() : window_(sf::VideoMode(640, 640), selectedUnit_(nullptr) {
    window_.setTitle("Пошаговая стратегия");
}

void GameUI::run() {
    while(window_.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void GameUI::handleEvents() {
    sf::Event event;
    while(window_.pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            window_.close();
        }
        else if(event.type == sf::Event::MouseButtonPressed) {
            if(event.mouseButton.button == sf::Mouse::Left) {
                int x = event.mouseButton.x / 64;
                int y = event.mouseButton.y / 64;
                handleClick(x, y);
            }
        }
    }
}

void GameUI::handleClick(int x, int y) {
    Unit* clickedUnit = game_.getUnitAt(x, y);

    if(clickedUnit && clickedUnit->getPlayer() == game_.getCurrentPlayer()) {
        selectedUnit_ = clickedUnit;
    }
    else if(selectedUnit_ && game_.getMap().isPassable(x, y)) {
        if(selectedUnit_->canMoveTo(x, y)) {
            selectedUnit_->move(x, y);
            game_.nextTurn();
        }
        selectedUnit_ = nullptr;
    }
}

void GameUI::update() {
    // Логика ИИ для компьютера
    if(game_.getCurrentPlayer() == 2) {
        // Простая логика ИИ
        for(auto& unit : game_.getUnits()) {
            if(unit.getPlayer() == 2) {
                // Просто двигаемся в случайном направлении
                int newX = unit.getX() + (rand() % 3 - 1);
                int newY = unit.getY() + (rand() % 3 - 1);

                if(game_.getMap().isPassable(newX, newY) && unit.canMoveTo(newX, newY)) {
                    unit.move(newX, newY);
                }
            }
        }
        game_.nextTurn();
    }
}

void GameUI::render() {
    window_.clear();

    // Рисуем карту
    game_.getMap().draw(window_);

    // Рисуем юнитов
    for(const auto& unit : game_.getUnits()) {
        window_.draw(unit.getSprite());
    }

    // Подсветка выбранного юнита
    if(selectedUnit_) {
        sf::RectangleShape selection(sf::Vector2f(64, 64));
        selection.setPosition(selectedUnit_->getX() * 64, selectedUnit_->getY() * 64);
        selection.setFillColor(sf::Color(255, 255, 255, 100));
        window_.draw(selection);
    }

    window_.display();
}