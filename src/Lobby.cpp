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

    //m_waveWindow = new wxScrolledWindow(this,wxID_ANY,wxPoint(10,220),wxSize(900,100));
    bt_refresh = new wxButton(this, 10105, "click", wxPoint(10,10), wxSize(50,20));
    //m_waveWindow->SetVirtualSize(wxSize(1000,100));
    ServerListFrame = new wxScrolledWindow(this,wxID_ANY,wxPoint(10,50),wxSize(400,400));
    ServerListFrame->SetScrollbars(1,2,10,10);
    ServerListFrame->SetScrollRate(1,1);
    ServerListFrame->SetVirtualSize(wxSize(500,1000));
    ServerListFrame->Show();
    rm_test_textctrl = new wxTextCtrl(ServerListFrame,wxID_ANY, wxEmptyString, wxPoint(30,30),wxSize(200,200),wxTE_MULTILINE);

    //below just some tests with the new widget
    //ServerLine * rm_test_svline1 = new ServerLine(ServerListFrame,wxID_ANY , wxPoint(0,400));

    //rm_test_textctrl->SetDefaultStyle(wxTextAttr(wxTE_MULTILINE));


}
/*void Lobby::DoSomethingInteresting(void *userData,Context& ctx){

auto reply = ctx.Get("http://jsonplaceholder.typicode.com/posts/1");

auto json = reply->GetBodyAsString();

rm_test_textctrl->AppendText(json);


}*/


/*static void SomethingInteresting(Context& ctx) {
    // Here we are in a co-routine, running in a worker-thread.

    // Asynchronously connect to a server and fetch some data.
    auto reply = ctx.Get("http://jsonplaceholder.typicode.com/posts/1");

    // Asynchronously fetch the entire data-set and return it as a string.
    auto json = reply->GetBodyAsString();

    // Just dump the data.
    cout << "Received data: " << json << endl;
}*/

void Lobby::nw_RequestJson(std::string url , int Action){
/*rapidjson::Document docc ;
std::string json_str = "" ;
auto rest_client = RestClient::Create();

rest_client->Process([=](Context& ctx){
auto reply = ctx.Get(url);

std::string json = reply->GetBodyAsString();
json_parse2action(json, Action);


//rm_test_textctrl->AppendText(json);
//json_str += "test";
});
*/
}
 void Lobby::json_parse2action(std::string json_str , int Action){
    //rapidjson::Document doccc ;
    ///doccc.Parse(json_str.c_str());
    if(Action == 1){
      RefreshLobby2(json_str);

    }

 }
void Lobby::RefreshLobby2(std::string  document){
rapidjson::Document doc ;
doc.Parse(document.c_str());

//int i = 0;

if(doc["Servers"].IsArray()){
    for(int i=0;i<doc["Servers"].Size();i++){//TODO SOLVE WARNING
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

       // currentline.bt_p->Connect(wxID_ANY,wxEvent)



        //LinesVector->push_back(currentline);
        //LinesVector->push_back(new ServerLine(ServerListFrame,wxID_ANY, wxPoint(10, 300+ i*30)));
    }

}

//rm_test_textctrl->AppendText(json);
}
void Lobby::RefreshLobby(){
nw_RequestJson("http://api.soldat.pl/v0/servers?empty=no&bots=no", 1);
}

void Lobby::OnBtRefresh_Click(wxCommandEvent&evt){
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

    wxCommandEvent eventt(MY_NEW_TYPE);
    eventt.SetString("This is the data");
    wxFrame* rm_testframe = new wxFrame(this, wxID_ANY, "SLST",wxPoint(30,30),wxSize(500,700));
    rm_testframe->Show();
// Then post the event
    //wxPostEvent(this, eventt); // to ourselves
//wxPostEvent(pBar, event);
    //RefreshLobby();



}
void Lobby::OnProcessA(wxCommandEvent & e){
rm_TestEvent();
//e->GetEventObject().SdtIp ;
//e.GetString()
wxObject * svln = e.GetEventObject();
wxString data = e.GetString() ;
rm_test_textctrl->AppendText(data);
//svln->IsKindOf(wxCLASSINFO(ServerLine));
//assert(false);
}
void Lobby::rm_TestEvent(){
    rm_test_textctrl->AppendText("\nx\n");


}
Lobby::~Lobby()
{
    //dtor
}
