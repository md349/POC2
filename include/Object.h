#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <ngl/Obj.h>

class Object
{
  public:
    //constructor
    Object();

    //creates a cute with centre at origin
    void createCube() const;

    //destructor
    ~Object();

  private:
    ngl::Obj *m_mesh;
    ngl::Vec3 m_cCoord;
    float m_cEdge;

};

#endif // OBJECT_H
