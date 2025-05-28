#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class GameMap {
public:
    GameMap();
    bool loadFromXml(const std::string& filename);
    bool isPassable(int x, int y) const;
    void draw(sf::RenderWindow& window) const;

private:
    std::vector<std::vector<sf::Sprite>> tiles_;
    std::vector<sf::Sprite> obstacles_;
    sf::Texture grassTexture_;
    sf::Texture waterTexture_;
    sf::Texture mountainTexture_;
};