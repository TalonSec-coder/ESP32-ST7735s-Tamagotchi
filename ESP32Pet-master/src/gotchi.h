#pragma once
#include <Arduino.h>

class Gotchi {
public:
  bool sleeping;
  int sleep;
  int hunger;
  int happiness;
  int age;
  int beardLength;
  int expression;
  int clothing;

  Gotchi(bool sleeping, int sleep, int hunger, int happiness, int age, int beardLength, int expression, int clothing);

  void updateSleeping();
  void updateSleep(int v);
  void updateHunger(int v);
  void updateHappiness(int v);
  void updateAge();

  void updateBeardLength(int v);
  void updateExpression(int v);
  void updateClothing(int v);

  // 👇 keep it here (clean + consistent)
  int mapValue(int val, int barLength);
};