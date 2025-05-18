#include "GLCanvas.h"
#include <wx/wx.h>

class MainApp : public wxApp {
public:
  virtual bool OnInit();
};

class MainWindow : public wxFrame {
public:
  MainWindow(const wxString &title);
};

wxIMPLEMENT_APP(MainApp);

bool MainApp::OnInit() {
  MainWindow *mainWindow = new MainWindow("wxOpenGL App");
  mainWindow->Show(true);
  return true;
}

MainWindow::MainWindow(const wxString &title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)) {
  new GLCanvas(this);
}
