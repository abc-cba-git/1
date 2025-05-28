#include "Game.h"

Game::Game() : currentPlayer_(1) {
    init();
}

void Game::init() {
    map_.loadFromXml("data/config/map.xml");

    // Добавляем юнитов для демонстрации
    addUnit(UnitType::WARRIOR, 2, 2, 1);
    addUnit(UnitType::ARCHER, 3, 3, 1);
    addUnit(UnitType::MAGE, 7, 7, 2);
}

void Game::nextTurn() {
    currentPlayer_ = currentPlayer_ == 1 ? 2 : 1;
}

void Game::addUnit(UnitType type, int x, int y, int player) {
    units_.emplace_back(type, x, y, player);
}

Unit* Game::getUnitAt(int x, int y) {
    for(auto& unit : units_) {
        if(unit.getX() == x && unit.getY() == y) {
            return &unit;
        }
    }
    return nullptr;
}