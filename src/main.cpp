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
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(900, 600)) {

  wxBoxSizer *mainSizer = new wxBoxSizer(wxHORIZONTAL);
  GLCanvas *glCanvas = new GLCanvas(this);
  mainSizer->Add(glCanvas, 1, wxEXPAND);
  SetSizer(mainSizer);
}
