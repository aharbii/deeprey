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

  wxGLContext *m_context;

  void InitializeGL();
  void DrawTriangle();

  wxDECLARE_EVENT_TABLE();
};

#endif // GLCANVAS_H
