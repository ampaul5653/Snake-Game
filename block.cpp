/*---------------------------------------------------------
 file: block.cpp
   by: Adam Paul
  org: COP 2001, Spring 2020
  for: Implementation file for a point class object
       by column and row
  ---------------------------------------------------------*/
#include "block.h"

//-------------------------------------------
// Constructors
//-------------------------------------------

/**********************************************************
   Default constructor of a point block class object,
   will instantiate an empty block
 parameters:
 returns: 
    Block(-1, -1)
**********************************************************/
Block::Block() {
    column = -1;
    row = -1;

    forward = nullptr;
    backward = nullptr;
}

/**********************************************************
 Instantiate a point block class object at a column and row
 parameters:
    columnIn - X-coordinate
    rowIn - Y-coordinate   
 returns:
    Block(columnIn, rowIn)
**********************************************************/
Block::Block(int columnIn, int rowIn) {
    column = columnIn;
    row = rowIn;

    forward = nullptr;
    backward = nullptr;
}

/**********************************************************
 Copy constructor sets block to column and row from another
 block
 parameters:
    other   - pointer to block to copy
 returns:
   
**********************************************************/
Block::Block(Block* other) {
   //copy the column and row values
    copy(other);

    forward = nullptr;
    backward = nullptr;
}

//-------------------------------------------
// Accessors
//-------------------------------------------

/**********************************************************
   Returns the current column property value
 parameters:
 returns:
    int - column value or -1 if empty
**********************************************************/
int Block::getColumn() {
    return column;
}

/**********************************************************
   Modify the current column property value
 parameters:
     columnIn - column value to set
 returns:
    void
**********************************************************/
void Block::setColumn(int columnIn) {   
    column = columnIn;
}

/**********************************************************
   Returns the current row property value
 parameters:
 returns:
    int - row value or -1 if empty
**********************************************************/
int Block::getRow() {
    return row;
}

/**********************************************************
   Modify the current column property value
 parameters:
     rowIn - row value to set
 returns:
    void
**********************************************************/
void Block::setRow(int rowIn) {
    row = rowIn;
}

/**********************************************************
 Returns a pointer to the block in front of this one
 parameters:
 returns:
    Block* - pointer to block or null
**********************************************************/
Block* Block::getForward() {
    return forward;
}

/**********************************************************
 Returns a pointer to the block behind this one 
 parameters:
 returns:
    Block* - pointer to block or null
**********************************************************/
Block* Block::getBackward() {
    return backward;
}

//-------------------------------------------
    // Methods
    //-------------------------------------------

/**********************************************************
   Determine if another block is the same as this one by
   column and row
 parameters:
    other  - block to check for equality
 returns:
    bool    - true if same column and row
**********************************************************/
bool Block::equals(Block other) {
    return column == other.getColumn() && row == other.getRow();
}

/**********************************************************
  Determine if this block is empty
 parameters:
 returns:
    bool - true if this block is empty
**********************************************************/
bool Block::isEmpty() {
    Block empty = Block();

    return equals(empty);
}

/**********************************************************
   Copy the values of another block to this one
 parameters:
    other  - block to copy
 returns:
    void
**********************************************************/
void Block::copy(Block* other) {
    column = other->getColumn();
    row = other->getRow();

    return;
}

/**********************************************************
 Link another block to the backward pointer of this one
 parameters:
    other  - block to link
 returns:
    void
**********************************************************/
void Block::append(Block* other) {
    backward = new Block(other);
    backward->forward = this;

    return;
}