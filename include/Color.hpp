#pragma once

#include <vector>

struct rgb {
    rgb(short _r, short _g, short _b)
     : r(_r), g(_g), b(_b) {}

    short r, g, b;

    bool operator==(const rgb& other) const {
        return r == other.r && g == other.g && b == other.b;
    }
};

struct rgbPair {
    rgbPair(short _c1, short _c2)
     : c1(_c1), c2(_c2) {}

    short c1, c2;

    bool operator==(const rgbPair& other) const {
        return c1 == other.c1 && c2 == other.c2;
    }
};

class Color {
public:
    static std::vector<rgb> colors;
    static std::vector<rgbPair> pairs;

    Color(rgb fore, rgb back);
    Color(short _n);

    short n;

    void start();
    void end();

    void* operator new[](size_t size);
    void operator delete[](void* ptr);
private:
    int addColor(rgb color);
};
