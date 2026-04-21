#ifndef SCROLL_MENU_H
#define SCROLL_MENU_H

#include <Arduino.h>

class ScrollMenu {
public:
    ScrollMenu(int x, int y, int menuSize);

    int x;
    int y;
    int menuSize;

    int prevSection;
    int activeSection;
    int nextSection;

    void moveRight();
    void moveLeft();

    int prev() const { return prevSection; }
    int next() const { return nextSection; }
};

#endif