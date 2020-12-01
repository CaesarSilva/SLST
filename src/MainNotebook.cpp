#include "MainNotebook.h"

MainNotebook::MainNotebook(wxWindow *parent, wxWindowID id, const wxPoint pos):wxNotebook()
{
    this->Create(parent,id,pos,wxSize(500,500));

//    rm_PgLobby = new wxPanel(this,wxID_ANY);
    PgLobby = new Lobby(this,wxID_ANY);
    PgNotifications = new NotificationTab(this, wxID_ANY);
    rm_PgEditor = new wxPanel(this,wxID_ANY);
    this->Show();
    this->AddPage(PgLobby, "LobbyReal");
    this->AddPage(PgNotifications, "Notifications");

 //   this->AddPage(rm_PgLobby, "Lobby");
    this->AddPage(rm_PgEditor, "Editor");



    //ctor
}

MainNotebook::~MainNotebook()
{
    //dtor
}
