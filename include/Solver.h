#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include <ngl/Vec3.h>

#include "Particle.h"

class Solver
{
  public:
    //default constructor
    Solver();

    //defined constructor
    Solver(int its);

    //Iteration control
    std::vector <Particle> iterationControl(const std::string &id);

    //destructor
    ~Solver();

   private:
      int m_iterations;
};

#endif // SOLVER_H
