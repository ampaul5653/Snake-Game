/*---------------------------------------------------------
 file: snakedefs.h
   by: Adam Paul
  org: COP 2001, Spring 2020
  for: Global configuration data for the snake game
  ---------------------------------------------------------*/
#pragma once

#include "console.h"

//---------------------------------------------------------
// Global Constants and Data Structures
//---------------------------------------------------------
const int WIDTH = 41; // Declare constants for our HDC object
const int HEIGHT = 41;
const int SCALE = 10;

const int CENTER_X = 21; //Declare a constant center coordinate (X,Y) for the snake
const int CENTER_Y = 21;

const Color BACKGROUND_COLOR = Black;
const Color SNAKE_COLOR = Teal;
const Color FOOD_COLOR = Silver;

enum Direction {
    None,
    Left,
    Right,
    Up,
    Down,
    Quit = -1
};
