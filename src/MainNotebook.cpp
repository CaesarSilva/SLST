#include "MainNotebook.h"

MainNotebook::MainNotebook(wxWindow *parent, wxWindowID id, const wxPoint pos):wxNotebook()
{
    this->Create(parent,id,pos,wxSize(600,500));
    PgLobby = new Lobby(this,wxID_ANY);
    PgNotifications = new NotificationTab(this, wxID_ANY);
    rm_PgEditor = new wxPanel(this,wxID_ANY);
    this->Show();
    this->AddPage(PgLobby, "Lobby");
    this->AddPage(PgNotifications, "Notifications");

    //this->AddPage(rm_PgEditor, "Editor");



    //ctor
}

MainNotebook::~MainNotebook()
{
    //dtor
}
