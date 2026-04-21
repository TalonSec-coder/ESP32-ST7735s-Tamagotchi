#include <Arduino.h>
#include <TFT_eSPI.h>
#include <EEPROM.h>

#include "gotchi.h"
#include "scroll_menu.h"
#include "sprites.h"

TFT_eSPI tft = TFT_eSPI();

#define LEFT 14
#define RIGHT 13
#define SELECT 27

ScrollMenu menu(58, 32, 6);

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

// ===== DECLARATIONS =====
void displayMenu();
void displayGotchi();
void displayStats();
void handleInput();
void changeState(const char* section);
void displaySleep();
void displayEat();
void displayPlay();
void displayCut();
void displayAge();

void setup() {

    Serial.begin(115200);
    EEPROM.begin(32);

    tft.init();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);

    pinMode(LEFT, INPUT_PULLUP);
    pinMode(RIGHT, INPUT_PULLUP);
    pinMode(SELECT, INPUT_PULLUP);

    displayGotchi();
    displayMenu();
    displayStats();
}

void loop() {

    handleInput();

    if(frameCount >= 40){
        displayGotchi();
        frameCount = 0;
    }

    frameCount++;
    delay(15);
}

// ===== INPUT =====
void handleInput(){

    if(!pressed){

        if(digitalRead(SELECT) == LOW){
            pressed = true;
            changeState(menuSections[menu.activeSection]);
        }

        else if(digitalRead(LEFT) == LOW){
            pressed = true;
            menu.moveLeft();
            displayMenu();
        }

        else if(digitalRead(RIGHT) == LOW){
            pressed = true;
            menu.moveRight();
            displayMenu();
        }
    }
    else if(digitalRead(LEFT) && digitalRead(RIGHT) && digitalRead(SELECT)){
        pressed = false;
    }
}

// ===== STATE HANDLER =====
void changeState(const char* section){

    delay(200);

    if(strcmp(section, "Sleep") == 0){
        gotchi.updateSleep(5);
        displaySleep();
    }

    else if(strcmp(section, "Play") == 0){
        gotchi.updateHappiness(3);
        displayPlay();
    }

    else if(strcmp(section, "Stats") == 0){
        displayAge();
    }

    else if(strcmp(section, "Eat") == 0){
        gotchi.updateHunger(5);
        displayEat();
    }

    else if(strcmp(section, "Cut") == 0){
        gotchi.updateBeardLength(0);
        displayCut();
    }

    else if(strcmp(section, "Dress") == 0){
        gotchi.updateClothing((gotchi.clothing + 1) % 4);
    }

    displayStats();
    displayMenu();
}

// ===== PET =====
void displayGotchi(){

    tft.fillRect(0, 20, 80, 80, TFT_BLACK);

    tft.drawRoundRect(20, 25, 60, 70, 5, TFT_WHITE);

    int x = 35;
    int y = 30;

    tft.drawBitmap(x, y + spriteOffset, bodyArray[gotchi.clothing], 32, 46, TFT_WHITE);
    tft.drawBitmap(x, y, feet, 32, 46, TFT_WHITE);
    tft.drawBitmap(x, y + spriteOffset, head, 32, 46, TFT_WHITE);
    tft.drawBitmap(x, y + spriteOffset, eyes, 32, 46, TFT_BLACK);

    if(gotchi.beardLength >= 24)
        tft.drawBitmap(x, y + spriteOffset, beard, 32, 46, TFT_WHITE);

    spriteOffset = (spriteOffset == -1) ? -2 : -1;
}

// ===== MENU =====
void displayMenu(){

    int y = 20;
    int h = 16;

    tft.fillRect(50, y, 100, 60, TFT_BLACK);

    tft.setTextColor(TFT_WHITE);

    tft.setCursor(menu.x + 19, y+4);
    tft.println(menuSections[menu.prev()]);
    tft.drawBitmap(menu.x, y+3, menuIcons[menu.prev()], 10, 10, TFT_WHITE);

    y += h;

    tft.drawRoundRect(menu.x-5, y, 90, h, 3, TFT_WHITE);
    tft.setCursor(menu.x + 19, y+4);
    tft.println(menuSections[menu.activeSection]);
    tft.drawBitmap(menu.x, y+3, menuIcons[menu.activeSection], 10, 10, TFT_WHITE);

    y += h;

    tft.setCursor(menu.x + 19, y+4);
    tft.println(menuSections[menu.next()]);
    tft.drawBitmap(menu.x, y+3, menuIcons[menu.next()], 10, 10, TFT_WHITE);
}

// ===== STATS =====
void displayStats(){

    tft.fillRect(0,0,160,20,TFT_BLACK);

    tft.setCursor(5,5);
    tft.print("Hun:");
    tft.print(gotchi.hunger);

    tft.setCursor(60,5);
    tft.print("Hap:");
    tft.print(gotchi.happiness);

    tft.setCursor(115,5);
    tft.print("Slp:");
    tft.print(gotchi.sleep);
}

// ===== ANIMATIONS =====
void displaySleep(){
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(60,60);
    tft.print("Zzz...");
    delay(800);
}

void displayEat(){
    for(int i=0;i<3;i++){
        tft.fillScreen(TFT_BLACK);
        tft.setCursor(60,60);
        tft.print("Eating...");
        delay(300);
    }
}

void displayPlay(){
    int x = 40;
    for(int i=0;i<60;i++){
        tft.fillScreen(TFT_BLACK);
        tft.fillCircle(x,60,5,TFT_WHITE);
        x += 3;
        if(x > 120) x = 40;
        delay(30);
    }
}

void displayCut(){
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(50,60);
    tft.print("Haircut!");
    delay(800);
}

void displayAge(){
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(40,60);
    tft.print("Age:");
    tft.print(gotchi.age);
    delay(1000);
}