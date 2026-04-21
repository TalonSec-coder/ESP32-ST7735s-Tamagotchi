#include <Arduino.h>
#include "scroll_menu.h"

ScrollMenu::ScrollMenu(int x, int y, int menuSize) {
    this->menuSize = menuSize;
    this->x = x;
    this->y = y;

    prevSection = 0;
    activeSection = 1;
    nextSection = 2;
}

void ScrollMenu::moveRight(){
    activeSection = (activeSection + 1) % menuSize;
    prevSection = (activeSection + menuSize - 1) % menuSize;
    nextSection = (activeSection + 1) % menuSize;
}

void ScrollMenu::moveLeft(){
    activeSection = (activeSection + menuSize - 1) % menuSize;
    prevSection = (activeSection + menuSize - 1) % menuSize;
    nextSection = (activeSection + 1) % menuSize;
}