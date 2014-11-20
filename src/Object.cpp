#include <iostream>
#include <ngl/VAOPrimitives.h>
#include <ngl/NGLInit.h>
#include "Object.h"

Object::Object()
{
  //We have code for a sphere, add obj loader as well
}

void Object::createCube() const{

}

Object::~Object()
{
  std::cout<<"Object dtor called!\n";
}
