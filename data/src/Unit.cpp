#include "Unit.h"
#include "tinyxml2.h"
#include <cmath>

using namespace tinyxml2;

Unit::Unit(UnitType type, int x, int y, int player)
    : type_(type), x_(x), y_(y), player_(player) {
    loadFromXml("data/config/units.xml");
}

void Unit::loadFromXml(const std::string& filename) {
    XMLDocument doc;
    doc.LoadFile(filename.c_str());

    const char* typeStr = "";
    switch(type_) {
        case UnitType::WARRIOR: typeStr = "warrior"; break;
        case UnitType::ARCHER: typeStr = "archer"; break;
        case UnitType::MAGE: typeStr = "mage"; break;
    }

    XMLElement* unit = doc.FirstChildElement("units")->FirstChildElement("unit");
    while(unit && strcmp(unit->Attribute("type"), typeStr) != 0) {
        unit = unit->NextSiblingElement("unit");
    }

    if(unit) {
        name_ = unit->FirstChildElement("name")->GetText();
        health_ = unit->FirstChildElement("health")->IntText();
        attack_ = unit->FirstChildElement("attack")->IntText();
        defense_ = unit->FirstChildElement("defense")->IntText();
        movement_ = unit->FirstChildElement("movement")->IntText();
        range_ = unit->FirstChildElement("range")->IntText();

        const char* texturePath = unit->FirstChildElement("texture")->GetText();
        texture_.loadFromFile(texturePath);
        sprite_.setTexture(texture_);
        sprite_.setPosition(x_ * 64, y_ * 64);
    }
}

bool Unit::canMoveTo(int x, int y) const {
    int dx = abs(x - x_);
    int dy = abs(y - y_);
    return (dx + dy) <= movement_ && x >= 0 && x < 10 && y >= 0 && y < 10;
}

void Unit::move(int x, int y) {
    x_ = x;
    y_ = y;
    sprite_.setPosition(x_ * 64, y_ * 64);
}

int Unit::attack(const Unit& target) const {
    return std::max(1, attack_ - target.defense_ / 2);
}