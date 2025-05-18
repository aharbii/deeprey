#include "GLCanvas.h"
#include <GL/gl.h>
#include <GL/glu.h>

wxBEGIN_EVENT_TABLE(GLCanvas, wxGLCanvas) EVT_PAINT(GLCanvas::OnPaint)
    EVT_SIZE(GLCanvas::OnResize) wxEND_EVENT_TABLE()

        GLCanvas::GLCanvas(wxWindow *parent)
    : wxGLCanvas(parent, wxID_ANY, nullptr), m_context(new wxGLContext(this)) {}

void GLCanvas::InitializeGL() {
  SetCurrent(*m_context);

  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glEnable(GL_DEPTH_TEST);
}

void GLCanvas::OnPaint(wxPaintEvent &event) {
  wxPaintDC dc(this);

  if (!m_context)
    return;

  SetCurrent(*m_context);
  InitializeGL();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  DrawTriangle();

  glFlush();
  SwapBuffers();
}

void GLCanvas::DrawTriangle() {
  glBegin(GL_TRIANGLES);
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex2f(-0.5f, -0.5f);

  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex2f(0.5f, -0.5f);

  glColor3f(0.0f, 0.0f, 1.0f);
  glVertex2f(0.0f, 0.5f);
  glEnd();
}

void GLCanvas::OnResize(wxSizeEvent &event) {
  if (!m_context)
    return;

  SetCurrent(*m_context);

  wxSize size = GetClientSize();
  glViewport(0, 0, size.GetWidth(), size.GetHeight());

  event.Skip();
}
