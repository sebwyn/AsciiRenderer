#pragma once

#include "World.hpp"

class Camera {
public:
    Camera(World* _world, int _x, int _y, int _winWidth, int _winHeight);
    
    int m_x, m_y;
    
    void update();
    void handleInput(int ch);

    void draw();
private:
    //the upper left hand corner position
    //in characters where char 0, 0 aligns with the upper left hand corner of 
    //tile 0, 0
    int winWidth, winHeight;
    
    bool wasPressed = false;
    int start_mx = 0;
    int start_my = 0;

    World* world;
};
