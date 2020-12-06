#ifndef SERVERINFO_H
#define SERVERINFO_H
#include "wx/wx.h"
#include "wx/sstream.h"
#include <wx/protocol/http.h>
#include "rapidjson/document.h"

#include "wx/socket.h"


//wxFrame* rm_testframe = new wxFrame(this, wxID_ANY, "SLST",wxPoint(30,30),wxSize(500,700));

class ServerInfo : public wxFrame
{
public:
    ServerInfo(wxWindow *parent, wxWindowID id, std::string ipport);
    virtual ~ServerInfo();
    void OnSocketEvent(wxSocketEvent& event);
    wxStaticText * Title = nullptr;
    wxStaticText * stx_GSyl = nullptr;
    wxStaticText * stx_NPlayersMax = nullptr;
    wxStaticText * SERVERINFO = nullptr;
    //wxTextCtrl * rm_test_textctrl = nullptr;
    unsigned int STEP = 0;
    int data1 ;
    std::string Sdt_Name,Sdt_Ip,Sdt_Map,Sdt_GStyle,Sdt_Country ;
    unsigned int Std_Port, Std_MaxPlayers,Std_NumPlayers;
    wxDECLARE_EVENT_TABLE();
protected:

private:
    void RequestServerInformation(std::string Ip, std::string Port, bool players);
    void updateinfo(std::string doc);
    void requestGamestats(std::string Ip, std::string Port);
    wxSocketClient *sclient;
};

#endif // SERVERINFO_H
