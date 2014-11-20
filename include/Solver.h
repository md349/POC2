#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include <ngl/Vec3.h>

#include "Particle.h"
#include "Hemisphere.h"
#include "Vertical.h"

class Solver
{
  public:
    //default constructor
    Solver();

    //defined constructor
    Solver(int its);

    //Iteration control
    std::vector <Particle> iterationControl(const std::string &id);

    //drawn moved particles
    std::vector <Particle> move(const std::string &id);
    //destructor
    ~Solver();

   private:
      int m_iterations;

      //create instances of the emitters
      Hemisphere h;
      Vertical v;
};

#endif // SOLVER_H
