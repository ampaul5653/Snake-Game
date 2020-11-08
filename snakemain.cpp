/*---------------------------------------------------------
 file: snakemain.cpp
   by: Adam Paul
  org: COP 2001, Spring 2020
  for: Driver file for the Snake game.
  ---------------------------------------------------------*/
#include <iostream>
#include <time.h> // for time function
#include <stdlib.h> //srand and rand

#include "snake.h" // Includes header file provided.

using namespace std;

//---------------------------------------------------------
// function prototypes
//---------------------------------------------------------
void update(Snake& snake, Block& food);
void render(HDC hdc, Snake snake, Block food);
Block nextFood(Snake snake);

int main() {
    HDC myConsole = initConsole(WIDTH, HEIGHT, SCALE); // Defines boundaries of console in game

    drawBorders(myConsole, WIDTH, HEIGHT, SCALE, White);
    drawBorders(myConsole, WIDTH, HEIGHT, SCALE, White);

    //initialize random numbers
    srand(time(NULL));

    Snake snake = Snake(CENTER_X,CENTER_Y);

    //current food pellet location
    Block food = nextFood(snake);

    // main game loop
    do {
        // process input
        if (snake.getNextDirection() == None)
            snake.setDirections(getGameKeys());

        // update game objects
        if (snake.getNextDirection() != Quit) {
            update(snake, food);
        }

        //draw the game
        render(myConsole, snake, food);
       
        
       Sleep(.05 * 1000); // pause for 1/5 of a second

    } while (snake.getNextDirection() != Quit); //end main game loop

    drawBorders(myConsole, WIDTH, HEIGHT, SCALE, White);

    return 0;
}
// end main

/********************************************************** 
    Updates game objects
 parameters:
    snake       - (out) our snake structure
    food        - (out) food block
 returns:
     void
**********************************************************/

void update(Snake& snake, Block& food) {

    if (snake.getNextDirection() != None) {
        snake.turn();
    }
    // see if snake has started moving yet
    if (snake.isMoving()) {
        //move
        snake.move();

        // see if snake ate food
        if (snake.getHead()->equals(food)) {
            //grow the snake
            snake.grow();
            
            //get a new food block
            food = nextFood(snake);
        }
        else {
            // see if snake has any collisions  
            snake.collisions();
        }
    }

    return;
}

/**********************************************************
 draws a snake block on the console window
 parameters:
    hdc     - handle to object to draw on
    snake   - snake structure
    food    - current food block
 returns:
     void
**********************************************************/
void render(HDC hdc, Snake snake, Block food){

    //draw food before snake so that the 
    //snake's head overwrites the food
    draw(hdc, food.getColumn(), food.getRow(), SCALE, FOOD_COLOR);

    //erase at old position
    if (!snake.getPrevTail()->isEmpty()) {
        draw(hdc, snake.getPrevTail()->getColumn(), snake.getPrevTail()->getRow(), SCALE, BACKGROUND_COLOR);
    }
    // draw at new location
    draw(hdc, snake.getHead()->getColumn(), snake.getHead()->getRow(), SCALE, SNAKE_COLOR);

    return;
}

/**********************************************************
 generates random location for new food
 parameters:
    snake   - snake class object
 returns:
     Block - location of next food pellet
**********************************************************/
Block nextFood(Snake snake) {
    Block food = Block();

    while (food.isEmpty()) { 

        food.setColumn(rand() % WIDTH); //random column
        food.setRow(rand() % HEIGHT); //random row

        //check if snake occupies this location
        if (snake.intersects(food,true)) {
            // set to empty if so
            food = Block();
        }    
    }

    return food;
}


