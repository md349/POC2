#ifndef BBOX_H
#define BBOX_H

#include <vector>
#include "Emitter.h"

class BBox : public Emitter
{
  public:
    void ID() const;

  private:
    std::vector <Particle> m_density;
};

#endif // BBOX_H
