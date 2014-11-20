#ifndef EMITTER_H
#define EMITTER_H

#include <iostream>
#include <vector>
#include <ngl/Vec3.h>

#include "Particle.h"

class Emitter
{
  public:
    //constructor, default settings wil throw an error
    Emitter(int _p = 100);

    void setPoints(const std::string &id);

    //add the required amount of particles to the particle vector
    //and set their initial attributes
    void addParticle(const float &prob, const std::string &id);

    //allows child classes to edit the number of particles
    void ChangeParticleNumber(const int &_p);

    //calls particle update function
    void trace(const std::string &id);

    //returns copy of Particle vector
    std::vector <Particle> getParticles(const std::string &id);

    //print the contents of the emitter
    void print(const std::string &id) const;

    //destructor
    ~Emitter();

  private:
    //number of particles
    int m_pnum;

    //vector to store hemisphere particles
    std::vector <Particle> m_htons;
    //vector to store verticle particles
    std::vector <Particle> m_vtons;

    //list to store particle positions in sphere
    std::vector <ngl::Vec3> m_eP;

    //list to store particle positions in vertical
    std::vector <ngl::Vec3> m_vP;

    //x coordinate for vertical emitter particle distribution
    float m_x;
    //z coordinate for vertical emitter particle distribution
    float m_z;

    //radius for set points
    const float m_radius = 0.5;
};

#endif // EMITTER_H
