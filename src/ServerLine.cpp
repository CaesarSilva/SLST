#include "ServerLine.h"

wxBEGIN_EVENT_TABLE(ServerLine,wxWindow)
    EVT_BUTTON(10111, ServerLine::OnBt_Click)
wxEND_EVENT_TABLE()



ServerLine::ServerLine(wxWindow *parent, wxWindowID id, wxPoint pos):wxWindow()
{
    this->Create(parent,id,pos,wxSize(500,30));
    /// THE POSITION VALUE IS USELESS, SINCE THE POSITION IS CHANGED ON THE PARENT WINDOW AFTER THE OBJECT IS CREATED
    //std::cout << "Inside Server Line Constructor" << std::endl;
    //this->Show();


    bt_p = new wxButton(this, 10111, wxEmptyString, wxPoint(5,10), wxSize(15,15));
    //ctor
}
void ServerLine::SetValues(unsigned int id,string Name, string Ip, int Port, int NumPlayers, int Maxplayers, string Country, string GStyle, string Map)
{
    ID = id;
    Sdt_Name = Name;
    Sdt_Ip = Ip;
    Sdt_Map = Map;
    Sdt_Country = Country;
    Sdt_GStyle = GStyle ;
    Std_Port = Port;
    Std_MaxPlayers = Maxplayers;
    Std_NumPlayers = NumPlayers;
    string ipport = Ip + ":" +std::to_string(Port);
    string players = std::to_string(Std_NumPlayers)+ "/"+std::to_string(Std_MaxPlayers);
    // wxWindow *f = static_cast<wxWindow*>(GetGrandParent());
    //Sdt_Name = f->GetName();
    stx_GSyl = new wxStaticText(this, wxID_ANY, Sdt_GStyle, wxPoint(310,5));
    stx_Name = new wxStaticText(this, wxID_ANY, Sdt_Name, wxPoint(45,5));

    stx_Country = new wxStaticText(this, wxID_ANY, Country, wxPoint(20,5));

    stx_IpPort = new wxStaticText(this, wxID_ANY, ipport, wxPoint(190,5));

    stx_NPlayersMax = new wxStaticText(this, wxID_ANY, players, wxPoint(340,5));
//    this->GetParent()->GetParent()->rm_TestEvent();


//f->rm_TestEvent();



}
void ServerLine::OnBt_Click(wxCommandEvent &evt)
{

    //https://wiki.wxwidgets.org/Beech:Creating_other_frames
    ///alternatives, comunicating with parent
    wxWindow *f = static_cast<wxWindow*>(GetGrandParent());
    //evt.SetEventObject(this);
    wxCommandEvent eventt(MY_NEW_TYPE);
    string ipport = Sdt_Ip + ":" +std::to_string(Std_Port);
    eventt.SetString(ipport);
// Then post the event
    wxPostEvent(f, eventt);
    f->ProcessWindowEvent(evt);
}
ServerLine::~ServerLine()
{
    //dtor
}
