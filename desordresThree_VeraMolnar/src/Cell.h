#pragma once
#ifndef __desordresThree_VeraMolnar__Cell__
#define __desordresThree_VeraMolnar__Cell__

#include <stdio.h>

#endif /* defined(__desordresThree_VeraMolnar__Cell__) */

class Cell {
 public:
    Cell();
    Cell(int x, int y);
    void create();
    void display();
    
    int mX;
    int mY;
    int rectSize;
    int numberOfInsets;
    bool hasSquare[8];
};