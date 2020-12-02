#include "NotificationTab.h"

wxBEGIN_EVENT_TABLE(NotificationTab,wxPanel)
//EVT_COMMAND(wxID_ANY, MY_NEW_TYPE, Lobby::OnProcessA)
EVT_BUTTON(10105, NotificationTab::rm_TestClick)
//EVT_TASKBAR_LEFT_DCLICK  (NotificationTab::OnTaskbarLClick)
EVT_TIMER(1100, NotificationTab::TimerUpdate)
wxEND_EVENT_TABLE()

NotificationTab * Ntab = nullptr;

NotificationTab::NotificationTab(wxWindow *parent, wxWindowID id)
{
    this->Create(parent,id);
    this->SetName("Notifications Class");
    //ctor
    Ntab = this;

    rm_test_textctrl = new wxTextCtrl(this,wxID_ANY, wxEmptyString, wxPoint(30,30),wxSize(200,200),wxTE_MULTILINE);
    rmbt = new wxButton(this, 10105, "click", wxPoint(10,10), wxSize(50,20));

    //wxString sIconPath = wxT("sample.ico");

    //wxIcon* pIcon = new wxIcon("./sample.ico");
    task->SetIcon(wxIcon("sample.ico"));
    //TODO put ini parsing inside a function to allow refreshing


INIReader reader("./ServersSearch.INI");
//    reader = new INIReader("./ServersSearch.INI");

    if (reader.ParseError() != 0) {
        std::cout << "Can't load 'test.ini'\n";
        rm_test_textctrl->AppendText("didnt work");
    }
    rm_test_textctrl->AppendText( reader.Get("test", "test1","NIE"));
for(int i=0 ; i<reader.GetInteger("info", "NumOfEntries", -1); i++){
        SvIniEntry  Svini;
       Svini.id = i;
        Svini.Ip = reader.Get("info", "ip"+std::to_string(i), "UNKNOWN") ;
        Svini.Port = reader.GetInteger("info", "port"+std::to_string(i), -1);
        Svini.Filters.MapList = reader.Get( std::to_string(i), "maplist" , "empty") ;
        Svini.Filters.MinPlayers = reader.GetInteger(std::to_string(i), "MinPlayers", 0);
        SvEntries.push_back(Svini);
    }


    m_timer = new wxTimer(this,1100);
    m_timer->Start(20000);

    AddNotification(std::string("test"),std::string("test1"),2);
    AddNotification(std::string("test"),std::string("test2"),2);
    AddNotification(std::string("test"),std::string("test3"),2);
    AddNotification(std::string("test"),std::string("test4"),2);
    AddNotification(std::string("test"),std::string("test5"),2);
}
void NotificationTab::LobbySearch(){
     //httplib::Client cli("http://api.soldat.pl");

    //auto res = cli.Get("/v0/servers?empty=no");
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
    rapidjson::Document doc ;
    //std::string document = res->body;
    std::string document = std::string(res.mb_str());

    std::cout << document.c_str() << std::endl;

    doc.Parse(document.c_str());
    //doc.Parse(res.c_str());
    if(doc["Servers"].IsArray()){
        for(int i=0; i<doc["Servers"].Size();i++){
            //rm_test_textctrl->AppendText("\ntSTest\n");

            for( auto ii : SvEntries){
            unsigned int Port, MaxP, NumP;

        std::string Name, Ip, GStyle, Country;
        wxString Map ;
            //rm_test_textctrl->AppendText("\ntTest\n");
            if(doc["Servers"][i]["IP"].IsString()) Ip= doc["Servers"][i]["IP"].GetString();
            if(doc["Servers"][i]["Port"].IsInt()) Port= doc["Servers"][i]["Port"].GetInt();
            if(doc["Servers"][i]["Port"].IsInt()) Map= doc["Servers"][i]["CurrentMap"].GetString();
            if(doc["Servers"][i]["NumPlayers"].IsInt()) NumP= doc["Servers"][i]["NumPlayers"].GetInt();
            //std::cout << ii.Ip << "  "<<Ip <<std::endl;
            //std::cout << ii.Port << "  "<<Port <<std::endl;
            if(Ip == ii.Ip && Port == ii.Port){
                rm_test_textctrl->AppendText("\ntSERVER FOUND\n");
                bool playersOk, enablemapsearch;
                playersOk = ii.Filters.MinPlayers <= NumP;
                std::cout << ii.Filters.MinPlayers << "   " << NumP << std::endl ;
                enablemapsearch = !(ii.Filters.MapList == "empty");
                std::cout << ii.Filters.MapList << "   " << "empty" << std::endl ;
                if(playersOk && enablemapsearch){//TODO check the search mode
                    tfile.Open("lists/"+ii.Filters.MapList);
                    wxString str ;
                    //str = tfile.GetFirstLine();
                    //std::cout << "first line " << str << std::endl ;
                    int aa = 0;

                    while(!tfile.Eof()){
                        if(aa==0)
                        {
                            str = tfile.GetFirstLine();
                        }else{
                            str = tfile.GetNextLine();
                        }

                        std::cout << "line " << aa << " " << str << std::endl ;
                        if(!str.IsEmpty()){
                            if(str == Map){
                               rm_test_textctrl->AppendText("Map found");
                            }
                        }
                        aa++;


                    }

                    tfile.Close();
                }

            }
            }
        }

    }


}
void NotificationTab::AddNotification(std::string Title, std::string Description , int type){
    Notification notification ;
    notification.Description = Description;
    notification.Title = Title;
    notification.type = type;
    Notifications.push_back(notification);

}
void NotificationTab::ShowNextNotification(){
if(!Notifications.empty()){
    Notification notification = Notifications.front() ;
    std::cout << "Notification " << notification.Description << notification.type << notification.Title << std::endl;
    NtMsg->SetMessage(notification.Description);
    NtMsg->SetTitle(notification.Title);
    NtMsg->Show(10);
    Notifications.erase(Notifications.begin());
}
}

void NotificationTab::rm_TestClick(wxCommandEvent &evt){
//wxNotificationMessage * NtMsg = new wxNotificationMessage(_("My title"), _("3 players are playing coop\n on rzal servers"));
NtMsg->Show(10);
rm_test_textctrl->AppendText("\nTest\n");

//INI PARSING TEST
/*wxFileConfig * config = new wxFileConfig( "", "", "ServersSearch.INI");
config->Read( wxT("/initScript"), &initializationFile);
config->Read( wxT("/scriptEditor"), &scrEd);
config->Read( wxT("/imageEditor"), &imgEd);*/
/*mINI::INIFile file("ServersSearch.INI");
mINI::INIStructure ini;
file.read(ini);

std::string testt = ini["test"]["test1"];
rm_test_textctrl->AppendText(testt);*/

    //reader.
    LobbySearch();

}
void NotificationTab::TimerUpdate(wxTimerEvent& evt){
    std::cout << "Timerupdate " << evt.GetInterval() << std::endl;
    if((evtTime % 2) == 0){
        ShowNextNotification();
    }
    if((evtTime % 10) ==0){
        LobbySearch();
    }
    evtTime++;

}
NotificationTab::~NotificationTab()
{
    delete NtMsg;
    delete task;

    //dtor
}
void NotificationTab::onTaskbarEvent(wxCommandEvent &evt){
wxWindow *f = static_cast<wxWindow*>(GetGrandParent());
f->Show();
}



wxBEGIN_EVENT_TABLE(Taskbar,wxTaskBarIcon)
//EVT_COMMAND(wxID_ANY, MY_NEW_TYPE, Lobby::OnProcessA)
//EVT_BUTTON(10105, NotificationTab::rm_TestClick)
    EVT_TASKBAR_LEFT_DCLICK(Taskbar::OnTaskbarLClick)
wxEND_EVENT_TABLE()

//Taskbar::Taskbar(){

//}
//Taskbar::~Taskbar(){

//}
void Taskbar::OnTaskbarLClick(wxTaskBarIconEvent &evt){
    //wxWindow *f = static_cast<wxWindow*>(GetGrandParent());
    wxWindow *f = static_cast<wxWindow*>(Ntab->GetGrandParent());
    f->Show();

    }
