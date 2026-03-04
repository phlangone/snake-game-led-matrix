# Snake Game on LED Matrix (MAX7219)

## Overview

This project implements the classic **Snake game** running on an **8x8 LED matrix** driven by the **MAX7219 LED controller** and controlled by an **Arduino-compatible microcontroller**.

The firmware is written in **C++** and structured using a **modular object-oriented design**, separating the display driver from the game logic.

Additionally, the system supports **external control via serial communication**, allowing a **Python script** running on a computer to send movement commands to the microcontroller.

This project was developed as an educational exercise in **embedded systems, SPI communication, and firmware architecture**.

---

## Features

- Classic Snake gameplay
- 8x8 LED matrix rendering
- MAX7219 display driver implemented from scratch
- Object-oriented firmware architecture
- Random food spawning
- Collision detection (walls and snake body)
- External control via **Python serial interface**

---

## Hardware Requirements

- Arduino Nano / Arduino Uno (or compatible)
- 8x8 LED matrix with **MAX7219 driver**
- USB connection to PC
- Computer running Python (optional, for external control)

---

## Wiring Example

Typical MAX7219 SPI connections:

| MAX7219 Pin | Arduino Pin |
|--------------|-------------|
| VCC | 5V |
| GND | GND |
| DIN | D11 (MOSI) |
| CS  | D10 |
| CLK | D13 (SCK) |

Pin numbers can be changed in the firmware constructor.

---

## Software Architecture

The project is organized into two main modules.

### 1. Display Driver (`DisplayDriver`)

Implements a **low-level driver for the MAX7219** LED controller using SPI.

Main capabilities:

- Display initialization
- Brightness control
- Scan configuration
- Pixel rendering
- Drawing primitives

Available drawing functions include:

```cpp
drawPixel()
clearDisplay()
fillDisplay()
fillRow()
drawBitmap()
drawLine()
```

This driver allows the LED matrix to be used as a **generic graphics display**.

---

### 2. Game Engine (`SnakeGame`)

The `SnakeGame` class inherits from the display driver and implements the full game logic.

Key responsibilities:

- Snake movement
- Direction control
- Food generation
- Collision detection
- Rendering game state

The snake body is stored as an array of points:

```cpp
struct Point {
    uint8_t row;
    uint8_t col;
};
```

The engine updates the game state on each loop iteration.

---

## Game Logic

The main loop follows a simple cycle:

1. Update snake position
2. Check if food was eaten
3. Detect collisions
4. Render the updated frame

When the snake eats food:

- The snake length increases
- A new food position is randomly generated

If the snake collides with:

- the screen boundary
- its own body

the game ends.

---

## Serial Control (Python Interface)

The project includes a **Python script** that allows controlling the snake through the computer keyboard.

File:

```
snake_control.py
```

The script sends commands through the serial port to change the snake direction.

Example directions:

- UP
- DOWN
- LEFT
- RIGHT

This makes the project useful for experimenting with **PC-to-microcontroller communication**.

---

## Project Structure

```
snake-game-led-matrix
│
├── example.ino
├── DisplayDriver.h
├── DisplayDriver.cpp
├── SnakeGame.h
├── SnakeGame.cpp
├── snake_control.py
└── README.md
```

---

## Compilation

Open `example.ino` using the **Arduino IDE** and upload it to your board.

Required Arduino libraries:

```
SPI
```

No external display libraries are required since the MAX7219 driver is implemented directly in the project.

---

## Possible Improvements

Future improvements may include:

- score tracking
- game restart after collision
- difficulty levels
- larger LED matrices
- sound effects (buzzer)
- joystick input instead of serial control

---

## Author

**Paulo H. Langone Miranda**  
Industrial Electronics – SENAI Anchieta

---

## License

MIT
