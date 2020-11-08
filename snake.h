/*---------------------------------------------------------
 file: snake.h
   by: Adam Paul
  org: COP 2001, Spring 2020
  for: Header file for a snake class object 
  ---------------------------------------------------------*/
#pragma once

#include "block.h"
#include "snakedefs.h"

class Snake {
private:
    Block head;     //root of the snake body

    Block* tail;    //pointer to last block in body

    Block prevTail; // for erasing and appending 

    Block speed;    // travelling velocity in the x/y axis

    int size;       // number of body blocks in snake

    Direction current; // curent direction snake is traveling
    Direction next;    // direction player has input

public:
//-------------------------------------------
// Constructors
//-------------------------------------------
    Snake();
    Snake(int startColumn, int startRow);
    

//-------------------------------------------
// Accessors
//-------------------------------------------
    Block* getHead();
    Block* getTail();
    Block* getPrevTail();
    int getSize();
    Direction getCurrentDirection();
    Direction getNextDirection();


//-------------------------------------------
// Methods
//-------------------------------------------

    void setDirections(int input);
    void turn();
    void move();
    bool isMoving();
    void grow();
    void collisions();
    bool intersects(Block other, bool withHead);

}; // end class Snake