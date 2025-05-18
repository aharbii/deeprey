#ifndef GLCANVAS_H
#define GLCANVAS_H

#include <wx/glcanvas.h>
#include <wx/wx.h>

class GLCanvas : public wxGLCanvas {
public:
  GLCanvas(wxWindow *parent);
  void Render();

private:
  void OnPaint(wxPaintEvent &event);
  void OnResize(wxSizeEvent &event);
  void OnIdle(wxIdleEvent &event);
  void OnMouseLeftDown(wxMouseEvent &event);

  wxGLContext *m_context;
  GLuint buttonTexture;
  int buttonWidth, buttonHeight;

  void InitializeGL();
  void DrawTriangle();
  void DrawOverlayButton();
  GLuint LoadTexture(const char *filePath);
  void LoadTextures();

  bool texturesLoaded;

  wxDECLARE_EVENT_TABLE();
};

#endif // GLCANVAS_H
