#include <iostream>
#include <math.h>

#include "Emitter.h"

Emitter::Emitter(int _p)
{
  //set number of particles, child emitters can edit this
  m_pnum = _p;
}

//set the origin point of particles on the emitters
void Emitter::setPoints(const std::string &id)
{
  //if we have a hemisphere emitter
  //create a list of particle points
  //this algorithm was derived from http://www.cplusplus.com/forum/general/65476/
  //and converted to work with NGL and as an emitter
  if(id == "h")
  {
    //define PI
    const float PI = 3.141592653589793238462643383279502884197;

    //Sphere Centre is origin
    const ngl::Vec3 centre (0,0,0);

    for (float phi = 0.0; phi < (m_pnum/100) * PI; phi += PI/10.0)
    {
      for (float theta = 0.0; theta < PI; theta += PI/10.0)
      {
        ngl::Vec3 point;
        point[0] = m_radius * cos(phi) * sin(theta) + centre[0];
        point[1] = m_radius * sin(phi) * sin(theta) + centre[1];
        point[2] = m_radius * cos(theta) + centre[2];
        m_eP.push_back(point);
      }
    }
    //std::cout<<"_eP size is : "<<_eP.size()<<"\n";
  }
  else if (id == "b")
  {
    //this is empty EDIT this
  }
  else if (id == "v")
  {
    //add particle distribution over a plane of SphereRadius*2 with centre 0,0,0
    //Increase in Y to be above the scene.
    const float _y = 0.7f; //change as the height of vertical emitter may vary.

    //Vectors for each vertex of the quad.
    //default Y height, may be too shallow for some scenes...
    ngl::Vec3 _v1 (-m_radius,_y,m_radius);
    ngl::Vec3 _v2 (m_radius,_y,m_radius);
    ngl::Vec3 _v3 (-m_radius,_y,-m_radius);
    ngl::Vec3 _v4 (m_radius,_y,-m_radius);

    //use ngl Random to generate random distribution of particles in vertical emitter
    //we need to generate 2 random numbers in the range of -2 to 2.
    //These will be added to a Vec3 where the Y is set to Y default height and the random
    //numbers make up the X and Z coordinates.
    ngl::Random *rand=ngl::Random::instance();

    for (int i = 0; i < m_pnum; ++i)
    {
      //put first four particles at the vertices of the quad.
      if (i < 4)
      {
        if(i == 0){m_vP.push_back(_v1);}
        if(i == 1){m_vP.push_back(_v2);}
        if(i == 2){m_vP.push_back(_v3);}
        if(i == 3){m_vP.push_back(_v4);}
      }
      //add the rest
      else
      {
        m_x = rand->randomNumber(m_radius);
        m_z = rand->randomNumber(m_radius);
        ngl::Vec3 _vpoint (m_x,_y,m_z);
        m_vP.push_back(_vpoint);
      }
    }
  }
  else
  {
    std::cout<<"Not a valid emitter type\n";
  }

}

//returns vector of particles based on type of emitter
std::vector <Particle> Emitter::getParticles(const std::string &id)
{
  if(id == "h"){return m_htons;}
  else if(id == "b"){return m_htons;} //EDIT
  else if(id == "v"){return m_vtons;}
}

//changes the total number of particles
void Emitter::ChangeParticleNumber(const int &_p)
{
  m_pnum = _p;
  std::cout<<"Child Emitter changed number of Particles to "<<m_pnum<<"\n";
}

//add particles to the particle vector.
void Emitter::addParticle(const float &prob, const std::string &id)
{
  for (int i = 0; i < m_pnum; ++i)
  {
    if(id == "h")
    {
      ngl::Vec3 pos = m_eP[i];
      Particle p(pos, prob);
      m_htons.push_back(p);
    }
    else if(id == "b")
    {
      //Particle p(pos);
      //_tons.push_back(p);
    }
    else if (id == "v")
    {
      ngl::Vec3 pos = m_vP[i];
      Particle p(pos, prob);
      m_vtons.push_back(p);
    }
    else
    {
      std::cout<<"No valid emitter!\n";
    }
  }
}

//calls update method in Particle class
//uses ray tracing techniques to trace the particles towards the origin
void Emitter::trace(const std::string &id)
{
  //The object will render at the origin. Therefore we need all particles
  //to travel towards the origin
  if (id == "h")
  {
    for (int i = 0; i < m_htons.size(); ++i)
    {
      m_htons[i].update(id);
    }
    std::cout<<"Complete\n";
  }
  else if(id == "b")
  {

  }
  else if(id == "v")
  {
    for (int i = 0; i < m_vtons.size(); ++i)
    {
      m_vtons[i].update(id);
    }
  }
  else
  {
    std::cout<<"No valid Emitter ID\n";
  }
}

void Emitter::print(const std::string &id) const
{
  if(id == "h"){
    //print out particle information
    for (int i = 0; i < m_htons.size(); ++i)
    {
      m_htons[i].particlePrint();
    }
  }
  else if(id == "b")
  {
    //EDIT
  }
  else if(id == "v")
  {
    //print out particle information
    for (int i = 0; i < m_vtons.size(); ++i)
    {
      m_vtons[i].particlePrint();
    }
  }
  else
  {
    std::cout<<"Not a valid emitter...nothing to print\n";
  }
}

Emitter::~Emitter()
{
  std::cout<<"Emitter dtor called!\n";
}
