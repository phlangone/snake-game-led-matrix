/*
  Author: Paulo H. Langone Miranda
  Date:   jul/2025
  Brief:  "Engine" for snake game
*/

// Standard C
#include <stdint.h>

// Arduino includes
#include <Arduino.h>

// Library include
#include "DisplayDriver.h"
#include "SnakeGame.h"

// Initialize game
void SnakeGame::begin() 
{
  DisplayDriver::begin();
  clearDisplay();
  setIntensity(INTENSITY_34);

  // Start with 3 points
  snakeLength = 3;
  snake[0] = {4, 4};  // head
  snake[1] = {4, 3};
  snake[2] = {4, 2};

  direction = RIGHT;

  spawnFood();
}

// Update snake positions, check if snake ate food or collide
void SnakeGame::update() 
{
  Point head = snake[0];
  Point newHead = head;

  switch (direction) 
  {
    case UP:    newHead.row = (head.row == 0) ? HEIGHT - 1 : head.row - 1; break;
    case DOWN:  newHead.row = (head.row + 1) % HEIGHT; break;
    case LEFT:  newHead.col = (head.col == 0) ? WIDTH - 1 : head.col - 1; break;
    case RIGHT: newHead.col = (head.col + 1) % WIDTH; break;
  }

  if (checkCollision(newHead)) 
  {
    begin(); // Game Over!
    return;
  }

  // Move snake body
  for (int i = snakeLength; i > 0; --i) 
  {
    snake[i] = snake[i - 1];
  }

  snake[0] = newHead;

  // Got food?
  if (newHead.row == food.row && newHead.col == food.col) 
  {
    snakeLength++;
    spawnFood();
  } 
}

// Draw snake points and food point on screen 
void SnakeGame::draw()
{
  clearDisplay();

  // Desenha a comida (sempre como pixel único)
  drawPixel(food.row, food.col);

  for (int i = 0; i < snakeLength;)
  {
    int start = i;
    int row = snake[i].row;

    // Verifica se os próximos pontos estão na mesma linha (horizontal)
    while (i + 1 < snakeLength && snake[i + 1].row == row)
    {
      i++;
    }

    if (i > start)
    {
      // Está em linha horizontal: monta o valor para fillRow
      uint8_t val = 0x00;
      for (int j = start; j <= i; j++)
      {
        val |= (1 << snake[j].col);
      }

      // Garante que a comida não desapareça da linha
      if (food.row == row)
      {
        val |= (1 << food.col);
      }

      fillRow(row, val);
    }
    else
    {
      uint8_t val = 0x00;
      if(food.row == row)
      {
        val |= ((1 << food.col) | (1 << snake[i].col));  
        fillRow(row, val);
      }
      else
      {
        drawPixel(snake[i].row, snake[i].col);
      }
    }

    i++;
  }
}

// Change snake movement direction
void SnakeGame::changeDirection(int newDir) 
{
  if ((direction == UP && newDir == DOWN) ||
      (direction == DOWN && newDir == UP) ||
      (direction == LEFT && newDir == RIGHT) ||
      (direction == RIGHT && newDir == LEFT)) 
  {
    return; // Ignore new direction in the same axis
  }

  direction = newDir;
}

// Spawn food on screen (random)
void SnakeGame::spawnFood() 
{
  while (true) 
  {
    food.row = random(0, HEIGHT);
    food.col = random(0, WIDTH);

    // Check if food do not collide with snake during spawn
    bool conflict = false;
    for (int i = 0; i < snakeLength; i++) 
    {
        if (snake[i].row == food.row && snake[i].col == food.col) 
        {
          conflict = true;
          break;
        }
    }

    if (!conflict) break;
  }
}

// Check for snake collision (end game)
bool SnakeGame::checkCollision(Point head) 
{
    for (int i = 0; i < snakeLength; i++) 
    {
        if (snake[i].row == head.row && snake[i].col == head.col) 
        {
            return true; // Collide (GAME OVER)
        }
    }

    return false;
}