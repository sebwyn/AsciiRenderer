#pragma once

#include <string>

#include "Color.hpp"

//these are the base renderables
//you can not render any world element smaller than this
class Tile {
public:
    static const int width = 10; 
    static const int height = 5;
    
    ~Tile();

    char** sprite;
    Color** colorMap;
    //id for use by world
    int type;
private:
    Tile(int _type, std::string _sprite, Color** _colorMap);
    bool verifyString(std::string str);

    friend class World;
};

#include "World.hpp"
