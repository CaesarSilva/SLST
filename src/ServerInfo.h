#ifndef SERVERINFO_H
#define SERVERINFO_H
#include "wx/wx.h"
#include "wx/sstream.h"
#include <wx/protocol/http.h>
#include "rapidjson/document.h"

#include "wx/socket.h"

#include "INIReader.h"


//wxFrame* rm_testframe = new wxFrame(this, wxID_ANY, "SLST",wxPoint(30,30),wxSize(500,700));

class ServerInfo : public wxFrame
{
public:
    ServerInfo(wxWindow *parent, wxWindowID id, std::string ipport);
    virtual ~ServerInfo();
    void OnSocketEvent(wxSocketEvent& event);
    void OnClick1(wxCommandEvent &evt);
    void OnClick2(wxCommandEvent &evt);
    void OnClick3(wxCommandEvent &evt);
    void OnClick4(wxCommandEvent &evt);
    wxStaticText * Title = nullptr;
    wxStaticText * stx_GSyl = nullptr;
    wxStaticText * stx_NPlayersMax = nullptr;
    wxStaticText * SERVERINFO = nullptr;
    wxButton * bt_Click1 = nullptr;
    wxButton * bt_Click2 = nullptr;
    wxButton * bt_Click3 = nullptr;
    wxButton * bt_Click4 = nullptr;//delete map
    wxWindow * windowsInfo = nullptr; //the purpose of this window is to facilitate the deletion of the statictexts on refresh

    std::string s1path, s2path , currentmap , mapspath, ip, port ;

    //wxTextCtrl * rm_test_textctrl = nullptr;
    unsigned int STEP = 0;
    int data1 ;
    std::string Sdt_Name,Sdt_Ip,Sdt_Map,Sdt_GStyle,Sdt_Country ;
    unsigned int Std_Port, Std_MaxPlayers,Std_NumPlayers;
    wxDECLARE_EVENT_TABLE();
    struct player{
        std::string Name;
        std::string Kills;
        std::string Deaths;
        std::string Team;
        std::string Ping;

    };
    std::vector<player> Players;


protected:

private:
    void RequestServerInformation(std::string Ip, std::string Port, bool players);
    void updateinfo(std::string doc);
    void requestGamestats(std::string Ip, std::string Port);
    wxSocketClient *sclient;
    void ParseGamestat(std::string wxstr);
};

#endif // SERVERINFO_H
