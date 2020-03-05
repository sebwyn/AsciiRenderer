#include "Game.hpp"

#include <iostream>

Game::Game(){}

void Game::run(){
    init();
    mainloop();
    cleanup();
}

void Game::init(){
    initscr();
    cbreak();
    noecho();
    
    keypad(stdscr, TRUE);
    //set to not wait for input
    nodelay(stdscr, TRUE);
    //curs_set(0);
    
    raw();
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    mouseinterval(0);

    start_color();
    use_default_colors();
    attron(A_BOLD);
    
    int winH, winW;
    getmaxyx(stdscr, winH, winW);
    //win = newwin(winH, winW, 0, 0);

    world=std::unique_ptr<World>(new World(10, 10));
    camera=std::unique_ptr<Camera>(new Camera(world.get(), 0, 0, winW-1, winH-1));
    whiteOnBlack=std::unique_ptr<Color>(new Color(rgb(999,999,999), rgb(0,0,0)));
    
    wbkgd(win, whiteOnBlack->n);
}

void Game::mainloop(){
    
    camera->draw();
    
    running = true;
    while(running){
         
        world->update();
        camera->update();

        //clear();
        /*Tile t = world->lookAt(0, 0);
        for(int x = 0; x < Tile::width; x++){
            for(int y = 0; y < Tile::height; y++){
                t.colorMap[x][y].start();
                mvaddch(y, x, t.sprite[x][y]);
                t.colorMap[x][y].end();
            }
        }*/
        //camera->draw();
        //move(25, 100);
        //addstr("Hello World!");
        refresh();

        //handle input (may move to its own class)
        int ch;
        if((ch = getch()) != ERR){
            switch(ch){ 
                case 'q':
                    running = false;
                    break;
                case 'w':
                    camera->m_y--;
                    //clear();
                    camera->draw();
                    break;
                case 'a':
                    camera->m_x--;
                    //clear();
                    camera->draw();
                    break;
                case 's':
                    camera->m_y++;
                    //clear();
                    camera->draw();
                    break;
                case 'd':
                    camera->m_x++;
                    //clear();
                    camera->draw();
                    break;
                default:
                    camera->handleInput(ch);
                    break;
            }   
        } 
    }
}

void Game::cleanup(){
    endwin();
}
