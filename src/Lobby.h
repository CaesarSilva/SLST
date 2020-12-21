#ifndef LOBBY_H
#define LOBBY_H
//#include <string>
#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/vector.h>
#include <vector>
#include "wx/sstream.h"
#include <wx/protocol/http.h>
#include "rapidjson/document.h"
#include <cstring>
#include "ServerLine.h"
#include "ServerInfo.h"
//wxDECLARE_EVENT(MY_NEW_TYPE, wxCommandEvent);
///Atention! I commented the line above because the event is already declared in ServerLine.h

class Lobby : public wxPanel
{

    public:
        Lobby(wxWindow *parent, wxWindowID id);
        virtual ~Lobby();




    public:
        wxScrolledWindow * ServerListFrame = nullptr;
        std::vector<ServerLine*>  LinesVector ;

        wxTextCtrl * rm_test_textctrl = nullptr;

        wxButton * bt_refresh = nullptr;
        void SortLines(std::string col , bool asc);
        void rm_TestEvent();
        void OnBtRefresh_Click(wxCommandEvent &evt);
        //network stuff below
        void nw_RequestJson(std::string url, int Action);
        //void DoSomethingInteresting(void *userData,Context& ctx);
        void json_parse2action(std::string json_str , int Action);
        void RefreshLobby2(std::string  document); // does the actual refreshing
        void RefreshLobby();//TODO remove this function with a function like action(int Action)
        void OnProcessA(wxCommandEvent & e);//WXUNUSED(e)
        wxDECLARE_EVENT_TABLE();
    protected:

    private:
};

#endif // LOBBY_H
