#include "Cell.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"
#include "cinder/app/App.h"

using namespace ci;

Cell::Cell()

{
}

Cell::Cell(int x, int y)
{
    mX = x;
    mY = y;
    rectSize = 100;
    numberOfInsets = 20;
    for (int i=0,j=sizeof(hasSquare); i<j; i++){
        if (Rand::randFloat(0, 100) >= 10) {
            hasSquare[i] = true;
        }
        else{ hasSquare[i] = false; }
    }
}

void Cell::display()
{
    gl::color( 0, 0, 1 ); // set color to blue
    for (int i=0, j=0; i<rectSize; i+=rectSize/numberOfInsets)
    {
        j++;
        if (hasSquare[j] == TRUE) {
            gl::drawStrokedRect( Rectf( mX+i, mY+i, mX+(rectSize-i), mY+(rectSize-i)), 2);
        }
    }
}

