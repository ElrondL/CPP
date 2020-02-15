/** file: test-springmass-graphics.cpp
 ** brief: Tests the spring mass simulation with graphics
 ** author: Andrea Vedaldi
 **/
// worked on by ©Jiaqi Li University of Oxford


#include "graphics.h"
#include "springmass.h"

#include <iostream>
#include <sstream>
#include <iomanip>

/* ---------------------------------------------------------------- */
class SpringMassDrawable : public SpringMass, public Drawable
/* ---------------------------------------------------------------- */
{

private:
    Figure figure ;
    
public:
    SpringMassDrawable()
    : figure("Bouncing SpringMass")
    {
        figure.addDrawable(this) ;
    }
    
    void draw() {
        figure.drawCircle(mass1->getPosition().x,mass1->getPosition().y,mass1->getRadius()) ;
        figure.drawCircle(mass2->getPosition().x,mass2->getPosition().y,mass2->getRadius()) ;
    figure.drawLine(mass1->getPosition().x,mass1->getPosition().y,mass2->getPosition().x,mass2->getPosition().y, 0.1) ;
    }
    
    void display() {
        figure.update() ;
    }
} ;


int main(int argc, char** argv)
{
  glutInit(&argc,argv) ;

  SpringMassDrawable springmass ;
  run(&springmass, 1/120.0) ;
    
  return 0 ;
}
