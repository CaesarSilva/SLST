#include "Lobby.h"
wxDEFINE_EVENT(MY_NEW_TYPE, wxCommandEvent);
wxBEGIN_EVENT_TABLE(Lobby,wxPanel)
    EVT_COMMAND(wxID_ANY, MY_NEW_TYPE, Lobby::OnProcessA)
    EVT_BUTTON(10105, Lobby::OnBtRefresh_Click)
wxEND_EVENT_TABLE()

Lobby::Lobby(wxWindow *parent, wxWindowID id):wxPanel()
{
    this->Create(parent,id);
    this->SetName("Lobby Class");
    //ctor
    bt_refresh = new wxButton(this, 10105, "click", wxPoint(10,10), wxSize(50,20));
    ServerListFrame = new wxScrolledWindow(this,wxID_ANY,wxPoint(10,50),wxSize(400,400));
    ServerListFrame->SetScrollbars(1,2,10,10);
    ServerListFrame->SetScrollRate(1,1);
    ServerListFrame->SetVirtualSize(wxSize(500,300));
    ServerListFrame->Show();
    rm_test_textctrl = new wxTextCtrl(ServerListFrame,wxID_ANY, wxEmptyString, wxPoint(30,30),wxSize(200,200),wxTE_MULTILINE);

}
void Lobby::SortLines(std::string col, bool asc)
{
    //TODO CHECK IF THIS FUNCTIONS CAUSES LAG
    if(col == "NumP")
    {


        sort(LinesVector.begin(), LinesVector.end(), [&]( ServerLine*& lhs,  ServerLine*& rhs)
        {
            return ((lhs->Std_NumPlayers > rhs->Std_NumPlayers) && asc) ||
             ((lhs->Std_NumPlayers < rhs->Std_NumPlayers) && !asc)
             ;
        });
        int i = 0;
        for(ServerLine * ii : LinesVector)
        {
            ii->SetPosition(wxPoint(5 , 300 + i*30));
            i++;
        }

    }

}
void Lobby::nw_RequestJson(std::string url, int Action)
{


}
void Lobby::json_parse2action(std::string json_str, int Action)
{
    if(Action == 1)
    {
        RefreshLobby2(json_str);

    }

}
void Lobby::RefreshLobby2(std::string  document)
{
    rapidjson::Document doc ;
    doc.Parse(document.c_str());
    doc.Parse(document.c_str());
    for(ServerLine * ii : LinesVector)
    {
        ii->Destroy();
    }
    LinesVector.clear();


    if(doc["Servers"].IsArray())
    {
        for(rapidjson::SizeType i=0; i<doc["Servers"].Size(); i++)
        {
            rm_test_textctrl->AppendText("\nSERVER INFO\n");
            rm_test_textctrl->AppendText(doc["Servers"][i]["Name"].GetString());
            unsigned int Port, MaxP, NumP;

            std::string Name, Ip, GStyle, Country, Map;
            if(doc["Servers"][i]["Name"].IsString()) Name= doc["Servers"][i]["Name"].GetString();
            if(doc["Servers"][i]["GameStyle"].IsString()) GStyle= doc["Servers"][i]["GameStyle"].GetString();
            if(doc["Servers"][i]["IP"].IsString()) Ip= doc["Servers"][i]["IP"].GetString();

            if(doc["Servers"][i]["Port"].IsInt()) Port= doc["Servers"][i]["Port"].GetInt();
            if(doc["Servers"][i]["MaxPlayers"].IsInt()) MaxP= doc["Servers"][i]["MaxPlayers"].GetInt();
            if(doc["Servers"][i]["NumPlayers"].IsInt()) NumP= doc["Servers"][i]["NumPlayers"].GetInt();
            ServerLine *currentline = (new ServerLine(ServerListFrame,wxID_ANY, wxPoint(5, 300+ i*30)));
            currentline->SetValues(i,Name,Ip,Port,NumP,MaxP,Country,GStyle,Map);
            LinesVector.push_back(currentline);
        }
        ServerListFrame->SetVirtualSize(wxSize(500,330+ 30*LinesVector.size()));
        SortLines("NumP", true);

    }
}
void Lobby::RefreshLobby()
{
    nw_RequestJson("http://api.soldat.pl/v0/servers?empty=no&bots=no", 1);
}

void Lobby::OnBtRefresh_Click(wxCommandEvent&evt)
{
    //httplib::Client cli("http://api.soldat.pl");

    //auto res = cli.Get("/v0/servers?empty=no");//&bots=no

    wxHTTP get;
    get.SetHeader(_T("Content-type"), _T("text/html; charset=utf-8"));
    get.SetTimeout(10);
    while (!get.Connect(_T("api.soldat.pl")))  // only the server, no pages here yet ...
        wxSleep(5);
    wxApp::IsMainLoopRunning();
    wxInputStream *httpStream = get.GetInputStream(_T("/v0/servers?empty=no"));
    //if (get.GetError() == wxPROTO_NOERR)
    //{
    wxString res;
    wxStringOutputStream out_stream(&res);
    httpStream->Read(out_stream);
    //}
    wxDELETE(httpStream);
    get.Close();
    std::string document = std::string(res.mb_str());
    json_parse2action(document, 1);
    //json_parse2action(res->body, 1);

    //wxCommandEvent eventt(MY_NEW_TYPE);
    //eventt.SetString("This is the data");
    //wxFrame* rm_testframe = new wxFrame(this, wxID_ANY, "SLST",wxPoint(30,30),wxSize(500,700));
    //rm_testframe->Show();
// Then post the event
    //wxPostEvent(this, eventt); // to ourselves
//wxPostEvent(pBar, event);
    //RefreshLobby();



}
void Lobby::OnProcessA(wxCommandEvent & e)
{
    rm_TestEvent();
//    wxObject * svln = e.GetEventObject();
    wxString data = e.GetString() ;
    ServerInfo * svinfo = new ServerInfo(this, wxID_ANY, std::string(data.mbc_str()));
    //rm_test_textctrl->AppendText(std::string(data.mbc_str()));

}
void Lobby::rm_TestEvent()
{
    rm_test_textctrl->AppendText("\nx\n");


}
Lobby::~Lobby()
{
    //dtor
}
