//This class is from BlankNGL. Original Author : Jon Macey
//Modified using lecture notes from GLSL lecture on 20/11/2014.

#include <QMouseEvent>
#include <QGuiApplication>

#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/Util.h>

#include <iostream>
#include <vector>

#include "Solver.h"
#include "Particle.h"

NGLScene::NGLScene(QWindow *_parent) : OpenGLWindow(_parent)
{
  // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
  setTitle("Particle Based Weathering System - Martin Davies");
  m_projection = ngl::perspective(50.0f,float(64/45),0.5,10);
  m_view = ngl::lookAt(ngl::Vec3(2,2,2), ngl::Vec3(0,0,0), ngl::Vec3(0,1,0));
}

NGLScene::~NGLScene()
{
  ngl::NGLInit *Init = ngl::NGLInit::instance();
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
  Init->NGLQuit();
}

void NGLScene::resizeEvent(QResizeEvent *_event )
{
  if(isExposed())
  {
  int w=_event->size().width();
  int h=_event->size().height();
  // set the viewport for openGL
  glViewport(0,0,w,h);
  renderLater();
  }
}

void NGLScene::initialize()
{
  // we need to initialise the NGL lib which will load all of the OpenGL functions, this must
  // be done once we have a valid GL context but before we call any GL commands. If we dont do
  // this everything will crash
  ngl::NGLInit::instance();
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);			   // Grey Background
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  // enable multisampling for smoother drawing
  glEnable(GL_MULTISAMPLE);
  // as re-size is not explicitly called we need to do this.
  glViewport(0,0,width(),height());

  //pointer to shader lib
  ngl::ShaderLib *shader = ngl::ShaderLib::instance();
  //create shader program and assign name
  shader->createShaderProgram("Colour");
  //create 2 empty shaders
  shader->attachShader("ColourVertex", ngl::VERTEX);
  shader->attachShader("ColourFragment", ngl::FRAGMENT);
  //load source for shaders
  shader->loadShaderSource("ColourVertex", "shaders/ColourVertex.glsl");
  shader->loadShaderSource("ColourFragment", "shaders/ColourFragment.glsl");
  //compile shaders
  shader->compileShader("ColourVertex");
  shader->compileShader("ColourFragment");
  //attach shader to program
  shader->attachShaderToProgram("Colour", "ColourVertex");
  shader->attachShaderToProgram("Colour", "ColourFragment");
  //link shader
  shader->linkProgramObject("Colour");
  shader->use("Colour");

  //get uniform in frag shader
  GLuint id = shader->getProgramID("Colour");
  GLuint uni = glGetUniformLocation(id,"lightPos");

  glUniform3f(uni,2.0f,1.0f,1.0f);
}

void NGLScene::render()
{
  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //begin Solver
  Solver s(1);
  m_HemiPoints = s.iterationControl("h");
  m_VertPoints = s.iterationControl("v");

  //instance of shader lib
  ngl::ShaderLib *shader = ngl::ShaderLib::instance();

  ngl::VAOPrimitives *prim = ngl::VAOPrimitives::instance();
  prim->createSphere("sphere",0.01,20);

  //translate
  ngl::Mat4 trans;

  //draw Hemisphere emitter
  for(int i = 0; i < m_HemiPoints.size(); ++i)
  {
    ngl::Vec3 loc = m_HemiPoints[i].getPosition();
    trans.translate(loc[0],loc[1],loc[2]);
    shader->setShaderParamFromMat4("MVP",trans*m_view*m_projection);
    prim->draw("sphere");
  }
  //draw Vertical emitter
  for(int i = 0; i < m_HemiPoints.size(); ++i)
  {
    ngl::Vec3 loc = m_VertPoints[i].getPosition();
    trans.translate(loc[0],loc[1],loc[2]);
    shader->setShaderParamFromMat4("MVP",trans*m_view*m_projection);
    prim->draw("sphere");
  }

  //trace the particles to the origin.
  //no graphical output is implemented. Text output is.
  //Particles also decide how they react with colliding with the origin here
  //provided as text output
  s.move("h");
  s.move("v");
}

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
  // escape key to quite
  case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
  default : break;
  }
  // finally update the GLWindow and re-draw
  if (isExposed())
    renderLater();
}
