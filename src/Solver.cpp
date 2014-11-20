#include <iostream>

#include "Solver.h"
//#include "Object.h"
#include "BBox.h"
#include "Hemisphere.h"
#include "Vertical.h"

Solver::Solver()
{
  m_iterations = 1;
}

Solver::Solver(int its)
{
  m_iterations = its;
}

std::vector <Particle> Solver::iterationControl(const std::string &id)
{
  //create instances of the emitters
  Hemisphere h;
  Vertical v;
  //begin iterations
  if (id == "h")
  {
    for(int i = 0; i < m_iterations; ++i)
    {
      h.ChangeParticleNumber(100);
      h.setPoints("h");
      h.addParticle(0.5,"h");
      h.print("h");
      //h.trace("h");
      //h.print("h");
    }
    //vector to add draw data to
    std::vector <Particle> drawData = h.getParticles("h");
    return drawData;
  }
  else if (id == "v")
  {
    for(int i = 0; i < m_iterations; ++i)
    {
      v.ChangeParticleNumber(200);
      v.setPoints("v");
      v.addParticle(0.5, "v");
      v.print("v");
      //v.trace("v");
      //v.print("v");
    }
    std::vector <Particle> drawData = v.getParticles("v");
    return drawData;
  }
}

Solver::~Solver()
{
  std::cout<<"Solver dtor called!\n";
}
