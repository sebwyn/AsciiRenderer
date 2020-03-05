#include "Color.hpp"

#include <string>

#include <ncurses.h>
#include <iostream>

std::vector<rgb> Color::colors;
std::vector<rgbPair> Color::pairs;

Color::Color(rgb fore, rgb back){
    rgbPair cPair = rgbPair(-1, -1);
    for(int i = 0; i < colors.size(); i++){
        if(fore == colors[i]) cPair.c1 = i;
        if(back == colors[i]) cPair.c2 = i;
    }
    if(cPair.c1 < 0) cPair.c1 = addColor(fore);
    if(cPair.c2 < 0) cPair.c2 = addColor(back);
    
    short r, g, b;
    color_content(cPair.c1, &r, &g, &b); 
    std::cout << "c1 is defined as: " << r << " " << g << " " << b << std::endl;
    color_content(cPair.c2, &r, &g, &b);
    std::cout << "c2 is defined as: " << r << " " << g << " " << b << std::endl; 
    
    
    n = -1;
    for(int i = 0; i < pairs.size(); i++){
        if(cPair == pairs[i]) n = i; 
    }
    if(n < 0 && cPair.c1 < COLOR_PAIRS && cPair.c2 < COLOR_PAIRS){
        std::cout << "Making New Color Pair" << std::endl;
        init_pair(pairs.size(), cPair.c1, cPair.c2);
        n = pairs.size();
        pairs.push_back(cPair);
    }
}

Color::Color(short _n)
 : n(_n){}

void Color::start(){
    attron(COLOR_PAIR(n));
}

void Color::end(){
    attroff(COLOR_PAIR(n));
}

void* Color::operator new[](size_t size){
    return malloc(size);
}

void Color::operator delete[](void* ptr){
    free(ptr);
}

int Color::addColor(rgb color){
    std::cout << "Making New Color" << std::endl;
    if(colors.size() < COLORS){
        init_color(colors.size(), color.r, color.g, color.b);
        colors.push_back(color);
    } else {
       throw std::string("Ran out of colors"); 
    }
    return (colors.size() - 1);
}


