#include "GameMap.h"
#include "tinyxml2.h"

using namespace tinyxml2;

GameMap::GameMap() {
    grassTexture_.loadFromFile("data/textures/tiles/grass.png");
    waterTexture_.loadFromFile("data/textures/tiles/water.png");
    mountainTexture_.loadFromFile("data/textures/tiles/mountain.png");
}

bool GameMap::loadFromXml(const std::string& filename) {
    XMLDocument doc;
    if(doc.LoadFile(filename.c_str()) != XML_SUCCESS) return false;

    tiles_.resize(10, std::vector<sf::Sprite>(10));

    XMLElement* tile = doc.FirstChildElement("map")->FirstChildElement("tiles")->FirstChildElement("tile");
    while(tile) {
        int x = tile->IntAttribute("x");
        int y = tile->IntAttribute("y");
        const char* type = tile->Attribute("type");

        sf::Sprite sprite;
        if(strcmp(type, "grass") == 0) sprite.setTexture(grassTexture_);
        else if(strcmp(type, "water") == 0) sprite.setTexture(waterTexture_);

        sprite.setPosition(x * 64, y * 64);
        tiles_[y][x] = sprite;

        tile = tile->NextSiblingElement("tile");
    }

    XMLElement* obstacle = doc.FirstChildElement("map")->FirstChildElement("obstacles")->FirstChildElement("obstacle");
    while(obstacle) {
        int x = obstacle->IntAttribute("x");
        int y = obstacle->IntAttribute("y");

        sf::Sprite sprite;
        sprite.setTexture(mountainTexture_);
        sprite.setPosition(x * 64, y * 64);
        obstacles_.push_back(sprite);

        obstacle = obstacle->NextSiblingElement("obstacle");
    }

    return true;
}

bool GameMap::isPassable(int x, int y) const {
    if(x < 0 || x >= 10 || y < 0 || y >= 10) return false;
    return tiles_[y][x].getTexture() == &grassTexture_;
}

void GameMap::draw(sf::RenderWindow& window) const {
    for(const auto& row : tiles_) {
        for(const auto& tile : row) {
            window.draw(tile);
        }
    }
    for(const auto& obstacle : obstacles_) {
        window.draw(obstacle);
    }
}