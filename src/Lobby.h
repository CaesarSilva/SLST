#ifndef LOBBY_H
#define LOBBY_H
//#include <string>
#include "httplib.h"
#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/vector.h>
#include <vector>

//below http libraries or other http stuff
/*#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
*/
//#define BOOST_LOG_DYN_LINK 1
//#include <boost/lexical_cast.hpp>
//#include <boost/fusion/adapted.hpp>
//#include <boost/log/trivial.hpp>
//#include <boost/log/utility/setup.hpp>

//#include "restc-cpp/restc-cpp.h"
#include "rapidjson/document.h" // JSON STUFF
//#include "rapidjson/encodings.h" // maybe that will solve the error
#include <cstring>
#include "ServerLine.h"
#include <memory>//TODO delete if not used

//#include "restc-cpp/SerializeJson.h"
//#include "restc-cpp/RequestBuilder.h"
//wxDECLARE_EVENT(MY_NEW_TYPE, wxCommandEvent);
///Atention! I commented the line above because the event is already declared in ServerLine.h
//using namespace std;
//using namespace restc_cpp;
//using namespace rapidjson;
/*struct Post {
    int userId = 0;
    int id = 0;
    std::string title;
    std::string body;
    };

BOOST_FUSION_ADAPT_STRUCT(
    Post,
    (int, userId)
    (int, id)
    (std::string, title)
    (std::string, body)
)
struct ServerPost {
    int MaxPlayers = 0;
    int NumPlayers = 0;
    std::string Name;
    std::string OS;
    };

BOOST_FUSION_ADAPT_STRUCT(
    ServerPost,
    (int, MaxPlayers)
    (int, NumPlayers)
    (std::string, Name)
    (std::string, OS)
)*/
class Lobby : public wxPanel
{

    public:
        Lobby(wxWindow *parent, wxWindowID id);
        virtual ~Lobby();




    public:
        wxScrolledWindow * ServerListFrame = nullptr;
        std::vector<ServerLine*> * LinesVector ;

        wxTextCtrl * rm_test_textctrl = nullptr;

        wxButton * bt_refresh = nullptr;

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
