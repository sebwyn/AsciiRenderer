#include "Camera.hpp"

#include <ncurses.h>
#include <cmath>
#include <iostream>

#include "Tile.hpp"

Camera::Camera(World* _world, int _x, int _y, int _winWidth, int _winHeight)
 : world(_world), m_x(_x), m_y(_y), winWidth(_winWidth), winHeight(_winHeight) {
    std::cout << "Screen has dimensions of "<<winWidth<<" "<<winHeight<<std::endl;
}

void Camera::update(){
    //change the winWidth && winHeight if necessary
    //update the X and Y as desired for cam mvmt
}

void Camera::handleInput(int ch){
    //std::cout << std::endl << "aight" << std::endl;
    if(ch == KEY_MOUSE){
        //std::cout << "Is mouse event" << std::endl;
        MEVENT event;
        if(getmouse(&event) == OK){
            switch(event.bstate){
                //std::cout << "Pressed" << std::endl;
                case(BUTTON1_PRESSED): {
                    wasPressed = true;
                    start_mx = event.x;
                    start_my = event.y;
                    int tileX = (m_x + event.x) / Tile::width;
                    int tileY = (m_y + event.y) / Tile::height;
                    //std::cout << tileX << " " << tileY << std::endl;
                    try {
                        world->placeAt(2, tileX, tileY);
                        draw();
                    } catch(std::string e) { 
                        //std::cout << e << std::endl;
                    }
                }
                break;
                case(BUTTON1_RELEASED): {
                    //std::cout << "Released" << std::endl;
                    if(wasPressed){
                        m_x -= event.x - start_mx;
                        m_y -= event.y - start_my;
                        draw();
                        wasPressed = false;
                    } 
                break;
                }
                default:
                    std::cout << "Something happened" << std::endl;
            }     
        }
    }
}

void Camera::draw(){
    //draw so that top corner of the square we are looking at is in the center
    //find the tile that 0, 0 is in
    
    for(int x = 0; x < winWidth; x++){
        for(int y = 0; y < winHeight; y++){
            int tileX = (m_x + x) / Tile::width;
            int tileY = (m_y + y) / Tile::height;
            if(tileX < 0 || tileX >= world->getWidth() 
            || tileY < 0 || tileY >= world->getHeight()
            || (m_x + x) < 0 || (m_y + y) < 0){
                mvaddch(y, x, ' ');
                continue;
            } else {
                int spriteX = (m_x + x) % Tile::width;
                int spriteY = (m_y + y) % Tile::height;
                //std::cout << spriteX << " " <<  spriteY << std::endl; 
                Tile t = world->lookAt(tileX, tileY);
                t.colorMap[spriteX][spriteY].start();
                mvaddch(y, x, t.sprite[spriteX][spriteY]);
                t.colorMap[spriteX][spriteY].end();
            }
        }
    }

    /*
    int xTileStart = m_x / Tile::width;
    int yTileStart = m_y / Tile::height;
    int xTileEnd = (m_x + winWidth) / Tile::width;
    int yTileEnd = (m_y + winHeight) / Tile::height;
    for(int x = xTileStart; x <= xTileEnd; x++){
        if(x < 0 || x >= world->getWidth()) continue;
        int tileXPos = x*Tile::width - m_x;
        for(int y = yTileStart; y <= yTileEnd; y++){
            if(y < 0 || y  >= world->getHeight()) continue;
            int tileYPos = y*Tile::width - m_y;
            Tile t = world->lookAt(x, y);
            Color** colorMap = t.colorMap;
            char** sprite = t.sprite;
            for(int sX = 0; sX < Tile::width; sX++){
                if(tileXPos + sX < 0 || tileXPos + sX > winWidth ) continue;
                for(int sY = 0; sY < Tile::height; sY++){
                    if(tileYPos + sY < 0 || tileYPos + sY > winHeight){continue;}
                    //we can see this character
                    colorMap[sX][sY].start(); 
                    mvaddch(tileYPos+sY, tileXPos+sX, sprite[sX][sY]);
                    colorMap[sX][sY].end();
                }
            }
        }
    }*/
}
