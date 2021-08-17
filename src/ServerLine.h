#ifndef SERVERLINE_H
#define SERVERLINE_H
#include <wx/wx.h>
#include <sstream>
#include <string>
wxDECLARE_EVENT(MY_NEW_TYPE, wxCommandEvent);
using namespace std ;
class ServerLine : public wxWindow
{
    public:
        ServerLine(wxWindow *parent, wxWindowID id,wxPoint pos);
        virtual ~ServerLine();
        void SetValues(unsigned int id ,string Name, string Ip, int Port, int NumPlayers ,int Maxplayers, string Country , string GStyle , string Map);



    unsigned int ID ; //all ServerLines will receive an ID to better organize everything
    unsigned int numPlayers ; //number of players
    //todo create a SetValues function to set all these variables;

    //SDt prefix = Server Data ; Std = a typo, its supposed to be sdt
    string Sdt_Name,Sdt_Ip,Sdt_Map,Sdt_GStyle,Sdt_Country ;
    unsigned int Std_Port ;
    unsigned int Std_MaxPlayers;
    unsigned int Std_NumPlayers;

    wxStaticText * stx_Country = nullptr;
    wxStaticText * stx_Name = nullptr;
    wxStaticText * stx_IpPort = nullptr;
    wxStaticText * stx_GSyl = nullptr;
    wxStaticText * stx_NPlayersMax = nullptr;
    wxStaticText * stx_map = nullptr;
    wxButton * bt_p = nullptr;

    void OnBt_Click(wxCommandEvent &evt);
    wxDECLARE_EVENT_TABLE();
    protected:

    private:
};

#endif // SERVERLINE_H
