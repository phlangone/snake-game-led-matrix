/*
  Author: Paulo H. Langone Miranda
  Date:   jul/2025
  Brief:  "Engine" for snake game
*/

#ifndef SNAKEGAME_H
#define SNAKEGAME_H

// Standard C
#include <stdint.h>

// Arduino includes
#include <Arduino.h>

// Library include
#include "DisplayDriver.h"

// Enum for directions
enum Direction {
  UP, RIGHT, DOWN, LEFT
};

// Game main class
// Inherit DisplayDriver class
class SnakeGame : public DisplayDriver
{
  public:
    // Class constructor
    SnakeGame(uint8_t din, uint8_t cs, uint8_t clk) : DisplayDriver(din, cs, clk, MATRIX) {}

    // Initialize game
    void begin();    

    // Update snake positions, check if snake ate food or collide         
    void update();        

    // Draw snake points and food point on screen    
    void draw();              

    // Change snake movement direction
    void changeDirection(int newDir); 

  private:
    // Point (pixel) structure
    struct Point {
      uint8_t row;
      uint8_t col;
    };

    // Snake points array
    Point snake[64];     

    // Snake current lenght
    uint8_t snakeLength;

    // Current movement direction
    int direction;

    // Current food point
    Point food;

    // Spawn food on screen (random)
    void spawnFood();    

    // Check for snake collision (end game)
    bool checkCollision(Point head);  
};

#endif //SNAKEGAME_H