#include "GLCanvas.h"
#include "SOIL.h"
#include <GL/gl.h>
#include <GL/glu.h>

wxBEGIN_EVENT_TABLE(GLCanvas, wxGLCanvas) EVT_PAINT(GLCanvas::OnPaint)
    EVT_SIZE(GLCanvas::OnResize) EVT_IDLE(GLCanvas::OnIdle)
        EVT_LEFT_DOWN(GLCanvas::OnMouseLeftDown)
            wxEND_EVENT_TABLE() GLCanvas::GLCanvas(wxWindow *parent)
    : wxGLCanvas(parent, wxID_ANY, nullptr), m_context(new wxGLContext(this)),
      buttonTexture(0), texturesLoaded(false) {}

void GLCanvas::InitializeGL() {
  SetCurrent(*m_context);

  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glEnable(GL_DEPTH_TEST);
}

void GLCanvas::OnIdle(wxIdleEvent &event) {
  if (!texturesLoaded && IsShownOnScreen()) {
    LoadTextures();
    texturesLoaded = true;
    Refresh();
  }
}

void GLCanvas::LoadTextures() {
  SetCurrent(*m_context);
  std::string imagePath = "assets/button.png";
  buttonTexture = LoadTexture(imagePath.c_str());

  if (buttonTexture == 0) {
    wxLogError("Failed to load texture: %s", imagePath);
  }
}

GLuint GLCanvas::LoadTexture(const char *filePath) {
  if (!m_context) {
    wxLogError("OpenGL context is not initialized.");
    return 0;
  }

  SetCurrent(*m_context);

  GLuint texture = SOIL_load_OGL_texture(
      filePath, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

  if (texture == 0) {
    wxLogError("SOIL Error: %s", SOIL_last_result());
    return 0;
  }

  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height;
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);

  buttonWidth = width;
  buttonHeight = height;

  return texture;
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

  if (texturesLoaded) {
    DrawOverlayButton();
  }

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

void GLCanvas::DrawOverlayButton() {
  if (buttonTexture == 0)
    return;

  wxSize size = GetClientSize();
  int canvasWidth = size.GetWidth();
  int canvasHeight = size.GetHeight();

  float maxButtonWidth = canvasWidth * 0.1f;
  float aspectRatio =
      static_cast<float>(buttonWidth) / static_cast<float>(buttonHeight);

  float renderWidth = maxButtonWidth;
  float renderHeight = maxButtonWidth / aspectRatio;

  if (renderHeight > canvasHeight * 0.1f) {
    renderHeight = canvasHeight * 0.1f;
    renderWidth = renderHeight * aspectRatio;
  }

  int btnX = canvasWidth - renderWidth - 10;
  int btnY = 10;

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, buttonTexture);

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0, canvasWidth, canvasHeight, 0, -1, 1);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex2f(btnX, btnY + renderHeight);
  glTexCoord2f(1.0f, 1.0f);
  glVertex2f(btnX + renderWidth, btnY + renderHeight);
  glTexCoord2f(1.0f, 0.0f);
  glVertex2f(btnX + renderWidth, btnY);
  glTexCoord2f(0.0f, 0.0f);
  glVertex2f(btnX, btnY);
  glEnd();

  glDisable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);

  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}

void GLCanvas::OnResize(wxSizeEvent &event) {
  if (!m_context)
    return;

  SetCurrent(*m_context);

  wxSize size = GetClientSize();
  glViewport(0, 0, size.GetWidth(), size.GetHeight());

  event.Skip();
}

void GLCanvas::OnMouseLeftDown(wxMouseEvent &event) {
  int x = event.GetX();
  int y = event.GetY();
  wxSize size = GetClientSize();

  int btnX = size.GetWidth() - buttonWidth - 10;
  int btnY = 10;

  if (x >= btnX && x <= btnX + buttonWidth && y >= btnY &&
      y <= btnY + buttonHeight) {
    wxLogMessage("Overlay Button Clicked!");
  }
}
