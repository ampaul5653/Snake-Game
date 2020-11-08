/*---------------------------------------------------------
 file: block.h
   by: Adam Paul
  org: COP 2001, Spring 2020
  for: Header file for a point class object by column and row
  ---------------------------------------------------------*/
#pragma once // only include this header in the preparser 
             // output file once

class Block {
private:

    int column; // X-coordinate
    int row; // Y-coordinate

    Block* forward; // points at body block in front of this one or null
    Block* backward; // points at body block behind this one or null

public:

    //-------------------------------------------
    // Constructors
    //-------------------------------------------
    Block();
    Block(int columnIn, int rowIn);
    Block(Block* other);

    //-------------------------------------------
    // Accessors
    //-------------------------------------------
    int getColumn();
    void setColumn(int columnIn);

    int getRow();
    void setRow(int rowIn);

    Block* getForward();
    Block* getBackward();

    //-------------------------------------------
    // Methods
    //-------------------------------------------
    bool equals(Block other);
    bool isEmpty();
    void copy(Block* other);
    void append(Block* other);
}; // end class Block
