#pragma once
#include <string>
#include <SFML/Graphics.hpp>

enum class UnitType { BOY, ARCHER, MAGE };

class Unit {
public:
    Unit(UnitType type, int x, int y, int player);

    void loadFromXml(const std::string& filename);
    bool canMoveTo(int x, int y) const;
    void move(int x, int y);
    int attack(const Unit& target) const;

    // Getters
    UnitType getType() const { return type_; }
    int getX() const { return x_; }
    int getY() const { return y_; }
    int getPlayer() const { return player_; }
    const sf::Sprite& getSprite() const { return sprite_; }

private:
    UnitType type_;
    std::string name_;
    int health_;
    int attack_;
    int defense_;
    int movement_;
    int range_;
    int x_, y_;
    int player_;
    sf::Texture texture_;
    sf::Sprite sprite_;
};