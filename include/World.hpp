#pragma once

class World;

#include <vector>

#include "Tile.hpp"
#include "Entity.hpp"

class World {
private:
    void generate();
    void genTileSet();
public:
    World(int _width, int _height);
    ~World();

    void update();

    //inline int** getData(){return tileData;}
    inline int getWidth(){return width;}
    inline int getHeight(){return height;}
    inline std::vector<Entity> getEntities(){return entities;}

    Tile lookAt(int x, int y);
    Tile breakAt(int x, int y);
    Tile placeAt(int tileID, int x, int y);
    
    Entity* createEntity(int x, int y, Tile sprite);
private:
    int width, height;
    std::vector<Entity> entities;
    
    std::vector<Tile> tileSet;
    int** tileData;
};
