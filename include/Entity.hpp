#pragma once

class Entity;

#include "Tile.hpp"

class Entity {
public:
    Entity(int _x, int _y, Tile _sprite);

    void update();

    int x, y; 
    Tile sprite;
private:
    //TO DO: give an entity a list of behaviours that drive it
};
