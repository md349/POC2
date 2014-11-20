#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>

#include <ngl/Vec3.h>
#include <ngl/Random.h>

class Particle
{
  public:
    //only need position for BBox emission
    Particle(ngl::Vec3 _p);

    //we need probability of settling for Hemisphere emission.
    //_prob is used for this is Monte Carlo Russian Roulette
    Particle(ngl::Vec3 _p, float _prob);

    //update particle information
    void update(const std::string &id);

    //return particle position
    inline ngl::Vec3 getPosition() const {return m_Position;}

    //print particle information
    void particlePrint() const;

    ~Particle();

  private:
    //Particle Position
    ngl::Vec3 m_Position;

    //Motion Probabilities
    float m_Ks;
    float m_Kp;
    float m_Kf;

    //Particle attributes...2 for now, could add more
    float m_d; //dirt
    float m_h; //humidity

    //Probability that the particle settles
    float m_pr;

    //inidicator that particle has intersected.
    bool m_in;

    //each particle needs energy. If energy is 0 we settle.
    float m_en;
};

#endif // PARTICLE_H
