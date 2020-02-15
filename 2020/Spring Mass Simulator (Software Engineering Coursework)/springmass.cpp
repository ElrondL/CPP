/** file: springmass.cpp
 ** brief: SpringMass simulation implementation
 ** author: Andrea Vedaldi
 **/
// worked on by ©Jiaqi Li University of Oxford


#include "springmass.h"
#include <iostream>

/* ---------------------------------------------------------------- */
// class Mass
/* ---------------------------------------------------------------- */

Mass::Mass()
: position(0,0), velocity(0,0), force(0,0), mass(1), radius(1)
{ }

Mass::Mass(Vector2 position, Vector2 velocity, double mass, double radius)
: position(position), velocity(velocity), force(), mass(mass), radius(radius),
xmin(-1),xmax(1),ymin(-1),ymax(1)
{ }

void Mass::setForce(Vector2 f)
{
  force = f ;
}

void Mass::addForce(Vector2 f)
{
  force = force + f ;
}

Vector2 Mass::getForce() const
{
  return force ;
}

Vector2 Mass::getPosition() const
{
  return position ;
}

Vector2 Mass::getVelocity() const
{
  return velocity ;
}

double Mass::getRadius() const
{
  return radius ;
}

double Mass::getMass() const
{
  return mass ;
}

double Mass::getEnergy(double gravity) const
{
  double energy = 0 ;

    energy = mass*gravity*position.y+0.5*mass*velocity.norm2();

  return energy ;
}

void Mass::step(double dt)
{
    double xp = position.x + velocity.x * dt + 0.5 * force.x * dt * dt;
    double yp = position.y + velocity.y * dt + 0.5 * force.y * dt * dt ;
    if (xmin + radius <= xp && xp <= xmax - radius) {
        position.x = xp ;
        velocity.x = velocity.x + force.x*dt;
    } else {
        velocity.x = -velocity.x ;
        force.x = -force.x;
    }
    if (ymin + radius <= yp && yp <= ymax - radius) {
        position.y = yp ;
        velocity.y = velocity.y + force.y*dt;
    } else {
        velocity.y = -velocity.y ;
        force.y = -force.y;
    }
}

/* ---------------------------------------------------------------- */
// class Spring
/* ---------------------------------------------------------------- */

Spring::Spring(Mass * mass1, Mass * mass2, double naturalLength, double stiffness, double damping)
: mass1(mass1), mass2(mass2),naturalLength(naturalLength), stiffness(stiffness), damping(damping)
{}

Mass * Spring::getMass1() const
{
  return mass1 ;
}

Mass * Spring::getMass2() const
{
  return mass2 ;
}

Vector2 Spring::getForce() const
{
  Vector2 F1, F2 ;

    F1 = stiffness*(naturalLength-getLength())*(mass2->getPosition() - mass1->getPosition())/naturalLength;
    F2.x = -F1.x;
    F2.y = -F1.y;

  return F1;
}

double Spring::getLength() const
{
  Vector2 u = mass2->getPosition() - mass1->getPosition() ;
  return u.norm() ;
}

double Spring::getEnergy() const {
  double length = getLength() ;
  double dl = length - naturalLength;
  return 0.5 * stiffness * dl * dl ;
}

std::ostream& operator << (std::ostream& os, const Mass& m)
{
  os<<"("
  <<m.getPosition().x<<","
  <<m.getPosition().y<<")" ;
  return os ;
}

std::ostream& operator << (std::ostream& os, const Spring& s)
{
  return os<<"$"<<s.getLength() ;
}

/* ---------------------------------------------------------------- */
// class SpringMass : public Simulation
/* ---------------------------------------------------------------- */

SpringMass::SpringMass(Mass * mass1, Mass * mass2, Spring * spring, double gravity)
: mass1(mass1), mass2(mass2), spring(spring), gravity(gravity)
{ }


SpringMass::SpringMass()
{
    const double mass = 0.05 ;
    const double radius = 0.05 ;
    const double naturalLength = 0.95 ;
    const double stiffness = 5;
    const double damping = 0.1;
    mass1 = new Mass(Vector2(-.5,0), Vector2(0, -0.5), mass, radius) ;
    mass2 = new Mass(Vector2(+.5,0), Vector2(0, 0), mass, radius) ;
    spring = new Spring(mass1, mass2, naturalLength, stiffness, damping);
    gravity = EARTH_GRAVITY;
}


void SpringMass::display()
{
    std::cout << mass1->getPosition().x << "," << mass1->getPosition().y << "," << mass2->getPosition().x << "," << mass2->getPosition().y << std::endl;
}

double SpringMass::getEnergy() const
{
  double energy = 0 ;

    energy = mass1->getEnergy(gravity)+mass2->getEnergy(gravity);

  return energy ;
}

void SpringMass::step(double dt)
{
  Vector2 g1(0,-gravity) ;
  Vector2 g2(1,-gravity) ;
    mass1->setForce(g1);
    mass2->setForce(g2);
    Vector2 f1 = spring->getForce();
    Vector2 f2;
    f2.x = -f1.x;
    f2.y = -f1.y;
    mass1->addForce(f1);
    mass2->addForce(f2);
    mass1->step(dt);
    mass2->step(dt);
    
}




