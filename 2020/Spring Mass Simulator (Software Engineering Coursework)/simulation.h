/** file: simulation.h
 ** brief: Simulation class (an interface)
 ** author: Andrea Vedaldi
 **/
// worked on by ©Jiaqi Li University of Oxford


#ifndef __simulation__
#define __simulation__

class Simulation
{
public:
    virtual void step(double dt) {};
    virtual void display() {} ;
    virtual void getEnergy() {} ;
} ;

#endif /* defined(__simulation__) */
