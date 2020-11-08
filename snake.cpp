/*---------------------------------------------------------
 file: snake.cpp
   by: Adam Paul
  org: COP 2001, Spring 2020
  for: Implementation file for a snake class object
---------------------------------------------------------*/
#include "snake.h"

//-------------------------------------------
// Constructors
//-------------------------------------------

/**********************************************************
   Default constructor of an empty snake where all
   variables are zero or null.
 parameters:
 returns:
**********************************************************/

Snake::Snake() {
    head = Block();        //root of the snake body

    tail = &head;          //ampersand gets the address of the 
                           //head and stores it in the tail pointer

    prevTail = Block();    // no previous tail (empty)

    speed = Block(0,0);    // speed = 0
    size = 1;              // 1 block (head)

    current = None;        // not moving
    next = None;           // no player input
}

/**********************************************************
 Set a new snake with head at starting column and row
parameters:
        startColumn     - x-coordinate for the head
        startRow        - y-coordinate for the head
returns:
**********************************************************/

Snake::Snake(int startColumn, int startRow) {
    head = Block(startColumn, startRow);        //root of the snake body

    tail = &head;                               //ampersand gets the address of the 
                                                //head and stores it in the tail pointer

    prevTail = Block();                         // empty previous tail
    prevTail.copy(tail);                        // set same as tail

    speed = Block(0, 0);                        // speed = 0
    size = 1;                                   // 1 block (head)

    current = None;                             // not moving
    next = None;                                // no player input
}


//-------------------------------------------
// Accessors
//-------------------------------------------

/**********************************************************
 Returns a pointer to the head of the snake
 parameters:
 returns:
    Block* - head block
**********************************************************/
Block* Snake::getHead() {
    return &head;
}

/**********************************************************
 Returns a pointer to the tail of the snake
 parameters:
 returns:
    Block* - tail block
**********************************************************/
Block* Snake::getTail() {
    return tail;
}

/**********************************************************
 Returns a pointer to the previous tail of the snake to
 erase it or append it if going
 parameters:
 returns:
    Block* - previous tail block 
**********************************************************/
Block* Snake::getPrevTail() {
    return &prevTail;
}

/**********************************************************
 Returns current size of snake in blocks
 parameters:
 returns:
    int  - size of snake
**********************************************************/
int Snake::getSize() {
    return size;
}

/**********************************************************
 Returns current direction snake is moving
 parameters:
 returns:
    direction  - current direction enum, None, or Quit
**********************************************************/
Direction Snake::getCurrentDirection() {
    return current;
}

/**********************************************************
 Returns next direction snake should move based on user
 input
 parameters:
 returns:
    direction  - current direction enum, None, or Quit
**********************************************************/
Direction Snake::getNextDirection() {
    return next;
}

//-------------------------------------------
// Methods
//-------------------------------------------

/**********************************************************
 Set next direction for the snake based on player input
 parameters:
    input  - console keyboard code
 returns:
     void
**********************************************************/

void Snake::setDirections(int input) {
    switch (input) {
        case VK_W:
        case VK_UP:
            if (current != Up && current != Down)
                next = Up;
            break;

        case VK_A:
        case VK_LEFT:
            if (current != Left && current != Right)
                next = Left;
            break;

        case VK_S:
        case VK_DOWN:
            if (current != Up && current != Down)
                next = Down;
            break;

        case VK_D:
        case VK_RIGHT:
            if (current != Left && current != Right)
                next = Right;
            break;

        case VK_X:
        case VK_ESCAPE:
            next = Quit;
            break;

        default:
            next = None;
        }

    return;
}

/**********************************************************
 Adjust speed of the snake based on directions to turn
 the snake
 parameters:
 returns:
     void
**********************************************************/
void Snake::turn() {

    current = next;
    next = None;

    // update velocities for change in direction
    switch (current) {
    case Up:
        speed.setRow(-1);
        speed.setColumn(0);
        break;

    case Left:
        speed.setRow(0);
        speed.setColumn(-1);
        break;

    case Down:
        speed.setRow(1);
        speed.setColumn(0);
        break;

    case Right:
        speed.setRow(0);
        speed.setColumn(1);
    }

    return;
}

/**********************************************************
 Move snake based on its speed
 parameters:
 returns:
     void
**********************************************************/
void Snake::move() {

    // save previous tail (x,y) location
    prevTail.copy(tail);

    // move up snake from tail to head copying (x,y) coordinates
    // from block in front to current block
    Block* temp = tail;
    while (temp) { 
        // if block in front of this one 
        if (temp->getForward()) {
            //then copy its values to this one
            temp->copy(temp->getForward());
        }

        //move temp pointer forward in snake
        temp = temp->getForward();
    }

    // adjust snake head for speed
    head.setColumn(head.getColumn() + speed.getColumn());
    head.setRow(head.getRow() + speed.getRow());

    return;
}

/**********************************************************
 Determine if the snake has a non-zero speed set
 parameters:
 returns:
     bool   - true if speed is not zero
**********************************************************/
bool Snake::isMoving() {
    Block zero = Block(0, 0);

    return !speed.equals(zero);
}

/**********************************************************
 Add a block on the tail of the snake when it eats food
 parameters:
 returns:
     void
**********************************************************/
void Snake::grow() {
    // increase snake size
    size++;

    // add old tail location back onto body at new index
    tail->append(&prevTail);

    // move tail pointer to new tail block
    tail = tail->getBackward();

    //make tail empty so that we dont erase it
    prevTail = Block();

    return;
}

/**********************************************************
See if snake collides with walls or itself and set 
nextDirection to Quit if so
parameters:
returns:
    void
**********************************************************/
void Snake::collisions() {
    bool noCollision = true;

    if (head.getColumn() <= 0) { // if hit left
        noCollision = false;
        head.setColumn(0);
    }
    else if (head.getColumn() >= WIDTH) { // if hit right
        noCollision = false;
        head.setColumn( WIDTH - 1);
    }

    if (head.getRow() <= 0) { // if hit top
        noCollision = false;
        head.setRow(0);
    }
    else if (head.getRow() >= HEIGHT) {
        noCollision = false;
        head.setRow(HEIGHT - 1); // if hit bottom
    }

    // check if snake hit self
    if (noCollision) {
        noCollision = !intersects(head, false);
    }

    //if collision then update head
    if (!noCollision) {
        next = Quit;
    }

    return;
}

/**********************************************************
Determine if a block intersects with the snake body
nextDirection to Quit if so
parameters:
    other       - the block to check
    withHead    - true if block is compared with head 
returns:
    boolean - true if block intersects body of snake
**********************************************************/

bool Snake::intersects(Block other, bool withHead) {
    bool collide = false;

    Block* temp = &head;

    //if not checking head then move pointer backwards
    if (!withHead) { 
        temp = head.getBackward();
    }

    //move along body checking each block against other
    while (temp && !collide) {
        collide = temp->equals(other);

        //move pointer to next body block
        temp = temp->getBackward();
    }

    return collide;
}
