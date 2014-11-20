#include <iostream>
#include <ngl/Random.h>
#include "Particle.h"


Particle::Particle(ngl::Vec3 _p)
{
   //set position inside the emitter
   m_Position = _p;

   //we only need the position for a BBox particle.
   //Set everything else to 0
   m_Ks = 0.0f;
   m_Kp = 0.0f;
   m_Kf = 0.0f;

   m_d = 0.0f;
   m_h = 0.0f;

   m_pr = 0.0f;

   m_in = false;

   m_en = 0.0f;
}

Particle::Particle(ngl::Vec3 _p, float _prob)
{

   //set the position as the inside of the emitter
   m_Position = _p;

   m_Ks = 0.1;
   m_Kp = 0.1;
   m_Kf = 0.1;

   //use random numbers for particle contents
   ngl::Random *rand=ngl::Random::instance();
   m_d = rand->randomPositiveNumber(1);
   m_h = rand->randomPositiveNumber(1);

   //assign kill probability to the particle.
   m_pr = _prob;

   //boolean to check whether intersection has occurred.
   m_in = false;

   //float for energy
   m_en = rand->randomPositiveNumber(1);
}

void Particle::update(const std::string &id)
{
  //t ranges between 0-1
  //paramter used to travel between points
  float t = 0.0f;
  //Vec3 for origin
  ngl::Vec3 origin (0,0,0);

  if (id == "h"){
   while (!m_in)
   {
      m_Position = (m_Position * (1 - t) + origin * t);
      if((m_Position[0] < 0 || m_Position[0] > 0) ||
         (m_Position[1] < 0 || m_Position[1] > 0) ||
         (m_Position[2] < 0 || m_Position[2] > 0)){
        //If we haven't reached the origin we need to check for intersection with object
        //before we increase t

        //increase t
        t += 0.01f;
      }
      else
      {
        m_in = true;
        //use random numbers for particle contents
        ngl::Random *rand=ngl::Random::instance();
        int action = rand->randomPositiveNumber(3);
        //std::cout<<"a random integer : "<<action<<"\n";
        //if 0 reflect
        if(action == 0)
        {
          std::cout<<"I have reflected!\n";
        }
        //if 1 bounced
        else if(action == 1)
        {
          std::cout<<"I have bounced!\n";
        }
        //if 2 settled
        else if(action == 2)
        {
          std::cout<<"I have settled!\n";
        }
      }
   }
  }
  else if (id == "b")
  {
    //EDIT
  }
  else if (id == "v")
  {
    //set the point we want to interpolate to
    origin[0] = m_Position[0];
    origin[2] = m_Position[2];
    while(!m_in)
    {
      m_Position = (m_Position * (1 - t) + origin * t);
      if(m_Position[1] < 0 || m_Position[1] > 0)
      {
        t += 0.01f;
      }
      else
      {
        m_in = true;
        //use random numbers for particle contents
        ngl::Random *rand=ngl::Random::instance();
        int action = rand->randomPositiveNumber(3);
        //std::cout<<"a random integer : "<<action<<"\n";
        //if 0 reflect
        if(action == 0)
        {
          std::cout<<"I have reflected!\n";
        }
        //if 1 bounced
        else if(action == 1)
        {
          std::cout<<"I have bounced!\n";
        }
        //if 2 settled
        else if(action == 2)
        {
          std::cout<<"I have settled!\n";
        }
      }
    }
  }
}

void Particle::particlePrint() const
{
  std::cout<<"Particle Position = ["<<m_Position[0]<<", "<<m_Position[1]<<", "<<m_Position[2]<<"]\n";
}

Particle::~Particle()
{
  //std::cout<<"Particle dtor called\n";
}

