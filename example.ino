/**
 * Example of snake game using keyboard arrows
 * Arduino is reading serial data writen from a python script
 */

#include "DisplayDriver.h"
#include "SnakeGame.h"

#define DIN_PIN 11
#define CS_PIN  10
#define CLK_PIN 13

SnakeGame game(DIN_PIN, CS_PIN, CLK_PIN);

unsigned long lastUpdate = 0;
const unsigned long interval = 200;

void setup() 
{
  Serial.begin(9600);
  game.begin();
}

void loop() 
{
  if (Serial.available()) 
  {
    char cmd = Serial.read();
    switch (cmd) 
    {
      case 'U': game.changeDirection(UP); break;
      case 'D': game.changeDirection(DOWN); break;
      case 'R': game.changeDirection(LEFT); break;
      case 'L': game.changeDirection(RIGHT); break;
    }
  }

  if (millis() - lastUpdate >= interval) 
  {
    lastUpdate = millis();
    game.update();
    game.draw();
  }
}
