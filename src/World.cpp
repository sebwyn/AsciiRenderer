#include "World.hpp"

#include <string>
#include <iostream>

World::World(int _width, int _height)
 : width(_width), height(_height){
    
    entities = std::vector<Entity>();
    tileSet = std::vector<Tile>();
     
    genTileSet();
    //populate the tileData
    generate();
}

World::~World(){
    for(int x = 0; x < width; x++){
        delete tileData[x];
    }
    delete tileData;
}

void World::generate(){
    tileData = new int*[width];
    for(int x = 0; x < width; x++){
        tileData[x] = new int[height];
        for(int y = 0; y < height; y++){
            //may use perlin noise here to generate different tile types
            tileData[x][y] = (x + y) % 2;
        }
    }
}


void World::update(){
    if(entities.size() > 0){
        for(Entity e : entities){
            e.update();
        }
    }
}

Tile World::lookAt(int x, int y){
    if(x<0 || x>width || y<0 || y>height) throw std::string("Out of range");
    if(tileData[x][y] > (int)tileSet.size()-1) throw std::string("invalid tile set");
    //otherwise
    return tileSet[tileData[x][y]];
}

Tile World::breakAt(int x, int y){
    Tile t = lookAt(x, y);
    //if lookAt doesn't throw than this is safe to continue
    tileData[x][y] = 0;
    return t;
}

Tile World::placeAt(int tileID, int x, int y){
    Tile oldT = lookAt(x, y);
    //if lookAt doesn't throw an error than we can continue 
    tileData[x][y] = tileID;
    return oldT;
}

Entity* World::createEntity(int x, int y, Tile sprite){
    entities.push_back(Entity(x, y, sprite));
    return &entities[entities.size() - 1];
}

void World::genTileSet(){
    Color whiteOnBlack = Color(rgb(999, 999, 999), rgb(0, 0, 0));
    Color** colorMap1 = new Color*[10];
    for(int x = 0; x < 10; x++){
        colorMap1[x] = (Color*)malloc(sizeof(Color)*5); 
        for(int y = 0; y < 5; y++){
            colorMap1[x][y] = whiteOnBlack;
        }
    }
    Color redOnBlack = Color(rgb(999, 0, 0), rgb(0, 0, 0));
    Color** colorMap2 = new Color*[10];
    for(int x = 0; x < 10; x++){
        colorMap2[x] = (Color*)malloc(sizeof(Color)*5); 
        for(int y = 0; y < 5; y++){
            colorMap2[x][y] = redOnBlack;
        }
    }

    std::string tile0Sprite = std::string( 
        "----------\n"
        "----------\n"
        "----------\n"
        "----------\n"
        "----------\n"
    );
    tileSet.push_back(Tile(0, tile0Sprite, colorMap1));

    std::string tile1Sprite = std::string(
        "@@@@@@@@@@\n"
        "@@@@@@@@@@\n"
        "@@@@@@@@@@\n"
        "@@@@@@@@@@\n"
        "@@@@@@@@@@\n"
    );
    tileSet.push_back(Tile(1, tile1Sprite, colorMap1));
    
    std::string tile2Sprite = std::string(
        "XXXXXXXXXX\n"
        "XXXXXXXXXX\n"
        "XXXXXXXXXX\n"
        "XXXXXXXXXX\n"
        "XXXXXXXXXX\n"
    );
    tileSet.push_back(Tile(2, tile2Sprite, colorMap2));
    
    for(int i = 0; i < Tile::width; i++){
        free(colorMap1[i]);
        free(colorMap2[i]);
    }
    delete[] colorMap1;
    delete[] colorMap2;
}
