#include "cMain.h"
wxBEGIN_EVENT_TABLE(cMain,wxFrame)
    EVT_BUTTON(10123, cMain::OnBt_Click)
wxEND_EVENT_TABLE()
cMain::cMain() :wxFrame(nullptr, wxID_ANY, "SLST",wxPoint(30,30),wxSize(650,700))
{
    //ctor
    m_btn = new wxButton(this, 10123, "Hide", wxPoint(10,10), wxSize(50,20));
    Notebook = new MainNotebook(this, wxID_ANY,wxPoint(30,30));

}

cMain::~cMain()
{
    //dtor
}
void cMain::OnBt_Click(wxCommandEvent &evt)
{

    Show(false);
}
