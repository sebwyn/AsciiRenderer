#include "Tile.hpp"

#include <cstring>
#include <sstream>

Tile::Tile(int _type, std::string _sprite, Color** _colorMap){
    if(!verifyString(_sprite)) throw std::string("Invalid Tile String");

    std::vector<std::string> spriteData;
    std::string line;
    std::stringstream stream(_sprite);
    while(getline(stream, line)){
        spriteData.push_back(line);
    }

    sprite = new char*[width];
    colorMap = new Color*[width];
    for(int x = 0; x < width; x++){
        sprite[x] = new char[height];
        for(int y = 0; y < width; y++){
            sprite[x][y] = spriteData[y][x];
        }
        colorMap[x] = (Color*)malloc(sizeof(Color)*height);
        memcpy(colorMap[x], _colorMap[x], sizeof(Color)*height);
    }
    type = _type;
}
    
Tile::~Tile(){
    //memory leak galore
    /*for(int i = 0; i < width; i++){
        delete[] sprite[i];
        free(colorMap[i]);
    }
    delete[] sprite;
    delete[] colorMap;*/
}

bool Tile::verifyString(std::string str){
    //verify string
    int sHeight = 0;
    int sWidth = -1;
    std::string line;
    std::stringstream stream(str);
    while(getline(stream, line)){
        if(sWidth == -1){
            sWidth = line.size();
        } else if(sWidth != line.size()) {
            return false;
        }
        
        sHeight++;    
    }
    if(sHeight != height || sWidth != width) return false;
    return true;
}
