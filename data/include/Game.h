#pragma once
#include <vector>
#include "Unit.h"
#include "GameMap.h"

class Game {
public:
    Game();

    void init();
    void nextTurn();
    void addUnit(UnitType type, int x, int y, int player);
    Unit* getUnitAt(int x, int y);
    const std::vector<Unit>& getUnits() const { return units_; }
    const GameMap& getMap() const { return map_; }
    int getCurrentPlayer() const { return currentPlayer_; }

private:
    std::vector<Unit> units_;
    GameMap map_;
    int currentPlayer_;
};