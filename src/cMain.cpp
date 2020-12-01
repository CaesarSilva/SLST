#include "cMain.h"
wxBEGIN_EVENT_TABLE(cMain,wxFrame)
EVT_BUTTON(10123, cMain::OnBt_Click)
wxEND_EVENT_TABLE()
cMain::cMain() :wxFrame(nullptr, wxID_ANY, "SLST",wxPoint(30,30),wxSize(500,700))
{
    //ctor
    m_btn = new wxButton(this, 10123, "Hide", wxPoint(10,10), wxSize(50,20));
    //m_btn1 = new wxButton(this, wxID_ANY, "lick", wxPoint(120,10), wxSize(25,25));

    /*rm_notebook = new wxNotebook(this,wxID_ANY, wxPoint(30,30), wxSize(300,300));
    rm_notebook->Show();
    rm_npage = new wxPanel(rm_notebook,wxID_ANY);
    rm_notebook->AddPage(rm_npage, "idk");
*/

    Notebook = new MainNotebook(this, wxID_ANY,wxPoint(30,30));

}

cMain::~cMain()
{
    //dtor
}
void cMain::OnBt_Click(wxCommandEvent &evt){

Show(false);
}
