#include "cApp.h"

wxIMPLEMENT_APP(cApp);
cApp::cApp()
{
    //ctor
}

cApp::~cApp()
{
    //dtor
}
bool cApp::OnInit()
{
    m_frame1 = new cMain();
    m_frame1 ->Show();
    return true;

}
