#include <Arduino.h>
#include <TFT_eSPI.h>
#include "esp_task_wdt.h"
#include <EEPROM.h>

#include "gotchi.h"
#include "scroll_menu.h"
#include "sprites.h"

TFT_eSPI tft = TFT_eSPI();

#define LEFT 14
#define RIGHT 13
#define SELECT 27

// ===== LAYOUT OFFSETS (FIXED) =====
#define PET_X 10
#define PET_Y 25

#define MENU_X 85
#define MENU_Y 30

#define STATS_Y 5

ScrollMenu menu(MENU_X, MENU_Y, 6);

bool pressed = false;
int frameCount = 0;
int spriteOffset = -1;

Gotchi gotchi(false, 12, 12, 12, 1, 0, 0, 0);

char menuSections[][20] = {
    "Cut","Dress","Eat","Stats","Play","Sleep"
};

const unsigned char* menuIcons[] = {
    beard_icon,dress_icon,eat_icon,stats_icon,play_icon,sleep_icon
};

const unsigned char* bodyArray[] = {
    myBitmapbody_01,myBitmapbody_02,myBitmapbody_03,myBitmapbody_04
};

// ===== FORWARD DECLARES =====
void displayMenu();
void displayPet();
void displayStats();
void handleInput();
void selectOption();
void animateEat();
void animatePlay();
void animateSleep();
void animateCut();
void showStatsScreen();

void setup() {

    Serial.begin(115200);
    EEPROM.begin(32);

    tft.init();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);

    pinMode(LEFT, INPUT_PULLUP);
    pinMode(RIGHT, INPUT_PULLUP);
    pinMode(SELECT, INPUT_PULLUP);

    displayStats();
    displayPet();
    displayMenu();
}

void loop() {

    handleInput();

    if(frameCount >= 20){
        displayPet();
        frameCount = 0;
    }

    frameCount++;
    delay(20);
}

// ===== INPUT =====
void handleInput(){

    if(!pressed){

        if(digitalRead(LEFT) == LOW){
            pressed = true;
            menu.moveLeft();
            displayMenu();
        }

        else if(digitalRead(RIGHT) == LOW){
            pressed = true;
            menu.moveRight();
            displayMenu();
        }

        else if(digitalRead(SELECT) == LOW){
            pressed = true;
            selectOption();
        }
    }
    else if(digitalRead(LEFT) && digitalRead(RIGHT) && digitalRead(SELECT)){
        pressed = false;
    }
}

// ===== MENU ACTION =====
void selectOption(){

    switch(menu.activeSection){

        case 0:
            animateCut();
            break;

        case 1:
            // dress (cycle outfit)
            gotchi.updateClothing((gotchi.clothing + 1) % 4);
            displayPet();
            break;

        case 2:
            animateEat();
            break;

        case 3:
            showStatsScreen();
            break;

        case 4:
            animatePlay();
            break;

        case 5:
            animateSleep();
            break;
    }

    displayStats();
    displayMenu();
}

// ===== PET =====
void displayPet(){

    tft.fillRect(PET_X, PET_Y, 70, 80, TFT_BLACK);

    tft.drawRoundRect(PET_X, PET_Y, 70, 80, 6, TFT_WHITE);

    int x = PET_X + 15;
    int y = PET_Y + 10;

    tft.drawBitmap(x, y + spriteOffset, bodyArray[gotchi.clothing], 32, 46, TFT_WHITE);
    tft.drawBitmap(x, y, feet, 32, 46, TFT_WHITE);
    tft.drawBitmap(x, y + spriteOffset, head, 32, 46, TFT_WHITE);
    tft.drawBitmap(x, y + spriteOffset, eyes, 32, 46, TFT_BLACK);

    spriteOffset = (spriteOffset == -1) ? -2 : -1;
}

// ===== MENU =====
void displayMenu(){

    tft.fillRect(MENU_X, MENU_Y, 70, 70, TFT_BLACK);

    int y = MENU_Y;

    tft.setTextColor(TFT_WHITE);

    // prev
    tft.setCursor(MENU_X + 15, y);
    tft.print(menuSections[menu.prev()]);
    tft.drawBitmap(MENU_X, y, menuIcons[menu.prev()], 10, 10, TFT_WHITE);

    y += 18;

    // active
    tft.drawRoundRect(MENU_X - 5, y - 2, 70, 16, 3, TFT_WHITE);
    tft.setCursor(MENU_X + 15, y);
    tft.print(menuSections[menu.activeSection]);
    tft.drawBitmap(MENU_X, y, menuIcons[menu.activeSection], 10, 10, TFT_WHITE);

    y += 18;

    // next
    tft.setCursor(MENU_X + 15, y);
    tft.print(menuSections[menu.next()]);
    tft.drawBitmap(MENU_X, y, menuIcons[menu.next()], 10, 10, TFT_WHITE);
}

// ===== STATS =====
void displayStats(){

    tft.fillRect(0, 0, 160, 20, TFT_BLACK);

    tft.setCursor(5, STATS_Y);
    tft.print("Hun:");
    tft.print(gotchi.hunger);

    tft.setCursor(55, STATS_Y);
    tft.print("Hap:");
    tft.print(gotchi.happiness);

    tft.setCursor(110, STATS_Y);
    tft.print("Slp:");
    tft.print(gotchi.sleep);
}

// ===== ANIMATIONS =====
void animateEat(){

    for(int i=0;i<3;i++){
        tft.fillScreen(TFT_BLACK);
        tft.setCursor(50,60);
        tft.print("Eating...");
        delay(300);
    }

    gotchi.updateHunger(5);
}

void animatePlay(){

    int x = 20;

    for(int i=0;i<60;i++){
        tft.fillScreen(TFT_BLACK);
        tft.fillCircle(x,60,5,TFT_WHITE);
        x += 3;
        if(x > 140) x = 20;
        delay(30);
    }

    gotchi.updateHappiness(3);
}

void animateSleep(){

    tft.fillScreen(TFT_BLACK);
    tft.setCursor(50,60);
    tft.print("Zzz...");
    delay(800);

    gotchi.updateSleep(5);
}

void animateCut(){

    tft.fillScreen(TFT_BLACK);
    tft.setCursor(50,60);
    tft.print("Haircut!");
    delay(800);

    gotchi.updateBeardLength(0);
}

void showStatsScreen(){

    tft.fillScreen(TFT_BLACK);
    tft.setCursor(40,60);
    tft.print("Age:");
    tft.print(gotchi.age);

    delay(1000);
}