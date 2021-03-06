#include "NotificationTab.h"

//#ifndef wxHAS_IMAGES_IN_RESOURCES
#include "SLST.xpm"
//#endif



wxBEGIN_EVENT_TABLE(NotificationTab,wxPanel)
//EVT_COMMAND(wxID_ANY, MY_NEW_TYPE, Lobby::OnProcessA)
    EVT_BUTTON(10105, NotificationTab::rm_TestClick)
//EVT_TASKBAR_LEFT_DCLICK  (NotificationTab::OnTaskbarLClick)
    EVT_TIMER(1100, NotificationTab::TimerUpdate)
wxEND_EVENT_TABLE()

NotificationTab * Ntab = nullptr;
//TODO REMOVE FUNCTION BELOW IF NOT NECESSARY


NotificationTab::NotificationTab(wxWindow *parent, wxWindowID id)
{
    this->Create(parent,id);
    this->SetName("Notifications Classs");
    //ctor
    Ntab = this;

    rm_test_textctrl = new wxTextCtrl(this,wxID_ANY, wxEmptyString, wxPoint(30,30),wxSize(200,200),wxTE_MULTILINE);
    rmbt = new wxButton(this, 10105, "click", wxPoint(10,10), wxSize(50,20));

    task->SetIcon(wxIcon(slst_xpm));
    NtMsg->SetFlags(wxICON_INFORMATION);
#ifdef __WXMSW__
    NtMsg->UseTaskBarIcon(task);
#endif // __WXMSW__
    if(task->IsIconInstalled())
    {
        std::cout << "Icon Installed" << std::endl ;
    }
    else
    {
        std::cout << "Icon Not Installed" << std::endl ;
    }
    if(task->IsOk())
    {
        std::cout << "Is ok true" << std::endl ;
    }
    else
    {
        std::cout << "Is ok false" << std::endl ;
    }
    if(task->IsAvailable())
    {
        std::cout << "system tray is available" << std::endl ;
    }
    else
    {
        std::cout << "system tray is not available" << std::endl ;
    }


    //TODO put ini parsing inside a function to allow refreshing


    INIReader reader("./ServersSearch.INI");

    if (reader.ParseError() != 0)
    {
        std::cout << "Can't load 'test.ini'\n";
        rm_test_textctrl->AppendText("didnt work");
    }
    rm_test_textctrl->AppendText( reader.Get("test", "test1","NIE"));
    for(int i=0 ; i<reader.GetInteger("info", "NumOfEntries", -1); i++)
    {
        std::cout << "Ini entry" << std::endl;
        SvIniEntry  Svini;
        Svini.id = i;
        Svini.Ip = reader.Get("info", "ip"+std::to_string(i), "UNKNOWN") ;
        Svini.Port = reader.GetInteger("info", "port"+std::to_string(i), -1);
        Svini.Filters.MapList = reader.Get( std::to_string(i), "maplist", "empty") ;
        Svini.Filters.MinPlayers = reader.GetInteger(std::to_string(i), "MinPlayers", 0);
        Svini.Title = reader.Get( std::to_string(i), "Title", "empty") ;
        Svini.Description = reader.Get( std::to_string(i), "Description", "empty") ;
        SvEntries.push_back(Svini);
    }


    m_timer = new wxTimer(this,1100);
    m_timer->Start(20000);


    //uncomment these lines down below to test the notifications
    //AddNotification(std::string("test"),std::string("test1"),2);
    //AddNotification(std::string("test"),std::string("test2"),2);
    //AddNotification(std::string("test"),std::string("test3"),2);
    //AddNotification(std::string("test"),std::string("test4"),2);
    //AddNotification(std::string("test"),std::string("test5"),2);
}
void NotificationTab::LobbySearch()
{
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

    //std::cout << document.c_str() << std::endl;

    doc.Parse(document.c_str());
    //doc.Parse(res.c_str());
    if(doc["Servers"].IsArray())
    {
        for(rapidjson::SizeType i=0; i<doc["Servers"].Size(); i++)
        {
            //rm_test_textctrl->AppendText("\ntSTest\n");

            for( auto ii : SvEntries)
            {

                unsigned int Port, NumP;

                std::string Name, Ip, GStyle, Country;
                wxString Map ;
                //rm_test_textctrl->AppendText("\ntTest\n");
                if(doc["Servers"][i]["IP"].IsString()) Ip= doc["Servers"][i]["IP"].GetString();
                if(doc["Servers"][i]["Port"].IsInt()) Port= doc["Servers"][i]["Port"].GetInt();
                if(doc["Servers"][i]["Port"].IsInt()) Map= doc["Servers"][i]["CurrentMap"].GetString();
                if(doc["Servers"][i]["NumPlayers"].IsInt()) NumP= doc["Servers"][i]["NumPlayers"].GetInt();
                //std::cout << ii.Ip << "  "<<Ip <<std::endl;
                //std::cout << ii.Port << "  "<<Port <<std::endl;
                //TODO add checkboxes to check if players
                if(Ip == ii.Ip && Port == ii.Port)
                {
                    rm_test_textctrl->AppendText("\ntSERVER FOUND\n");
                    bool playersOk, enablemapsearch;
                    bool MapOk=false;
                    playersOk = ii.Filters.MinPlayers <= NumP;
                    std::cout << ii.Filters.MinPlayers << "   " << NumP << std::endl ;
                    enablemapsearch = !(ii.Filters.MapList == "empty");
                    std::cout << ii.Filters.MapList << "   " << "empty" << std::endl ;
                    if(playersOk && enablemapsearch) //TODO check the search mode
                    {
                        tfile.Open("lists/"+ii.Filters.MapList);
                        wxString str ;
                        //str = tfile.GetFirstLine();
                        //std::cout << "first line " << str << std::endl ;
                        int aa = 0;

                        while(!tfile.Eof())
                        {
                            if(aa==0)
                            {
                                str = tfile.GetFirstLine();
                            }
                            else
                            {
                                str = tfile.GetNextLine();
                            }

                            //std::cout << "line " << aa << " " << str << std::endl ;
                            if(!str.IsEmpty())
                            {
                                if(str == Map)
                                {
                                    rm_test_textctrl->AppendText("Map found");

                                    //AddNotification(ii.Title, ii.Description,1);
                                    MapOk=true;
                                }
                            }
                            aa++;


                        }

                        tfile.Close();
                        std::cout << "End of map verification. MapOk:" << MapOk << std::endl;
                    }
                    else if(!enablemapsearch && playersOk) MapOk = true;
                    if(playersOk && MapOk)
                    {
                        AddNotification(ii,1,NumP,Map.ToStdString());

                    }
                    else
                    {
                        std::cout << "Notification not added. Playersok" << playersOk << "MapOk" << MapOk << std::endl;

                    }


                    //if(TriggerNotification)AddNotification(ii,1);

                }//Ip == ii.Ip && Port == ii.Port
            }
        }

    }


}
void NotificationTab::AddNotification(SvIniEntry entry, int type, unsigned int NumP, std::string Map)
{
    Notification notification ;
    notification.Description = entry.Description;
    notification.Title = entry.Title;
    std::size_t pos = notification.Description.find("$p");
    if(pos != std::string::npos)
    {
        notification.Description.replace(pos,2,std::to_string(NumP));
    }
    pos = notification.Description.find("$m");
    if(pos != std::string::npos)
    {
        notification.Description.replace(pos,2,Map);
    }
    pos = notification.Title.find("$p");
    if(pos != std::string::npos)
    {
        notification.Title.replace(pos,2,std::to_string(NumP));
    }
    pos = notification.Title.find("$m");
    if(pos != std::string::npos)
    {
        notification.Title.replace(pos,2,Map);
    }

    notification.type = type;
    Notifications.push_back(notification);


}
void NotificationTab::ShowNotification(std::string Title, std::string Description)
{
#ifdef __WXGTK210__
    char name[40] = "SLST";
    notify_init(name);
    NotifyNotification *example;
    example = notify_notification_new(Title.c_str(),Description.c_str(), "ic");
    std::cout << Title.c_str() << " " << Description.c_str() << std::endl;
    notify_notification_set_timeout(example,30000);
    char category[30] = "SLST Notification";
    notify_notification_set_category(example,category);
    notify_notification_set_urgency (example,NOTIFY_URGENCY_NORMAL);
    GError *error = NULL;
    notify_notification_show(example,&error);
#endif
#ifdef __WXMSW__
    NtMsg->SetMessage(Description);
    NtMsg->SetTitle(Title);
    NtMsg->Show(44);
#endif
}
void NotificationTab::ShowNextNotification()
{
    if(!Notifications.empty())
    {
        Notification notification = Notifications.front() ;
        std::cout << "Notification " << notification.Description << notification.type << notification.Title << std::endl;
        NtMsg->SetMessage(notification.Description);
        NtMsg->SetTitle(notification.Title);
        //NtMsg->Show(10);
        ShowNotification(notification.Title, notification.Description);
        Notifications.erase(Notifications.begin());
    }
}

void NotificationTab::rm_TestClick(wxCommandEvent &evt)
{
//wxNotificationMessage * NtMsg = new wxNotificationMessage(_("My title"), _("3 players are playing coop\n on rzal servers"));
//NtMsg->Show(10);
    rm_test_textctrl->AppendText("\nTest\n");
    //reader.
    LobbySearch();

}
void NotificationTab::TimerUpdate(wxTimerEvent& evt)
{
    std::cout << "Timerupdate " << evt.GetInterval() << std::endl;
    if((evtTime % 12) ==0)
    {
        LobbySearch();
    }
    if((evtTime % 2) == 0)
    {
        ShowNextNotification();
    }

    evtTime++;

}
NotificationTab::~NotificationTab()
{
    delete NtMsg;
    delete task;

    //dtor
}
void NotificationTab::onTaskbarEvent(wxCommandEvent &evt)
{
    wxWindow *f = static_cast<wxWindow*>(GetGrandParent());
    f->Show();
}



wxBEGIN_EVENT_TABLE(Taskbar,wxTaskBarIcon)
//EVT_COMMAND(wxID_ANY, MY_NEW_TYPE, Lobby::OnProcessA)
//EVT_BUTTON(10105, NotificationTab::rm_TestClick)
    EVT_TASKBAR_LEFT_DCLICK(Taskbar::OnTaskbarLClick)
wxEND_EVENT_TABLE()

void Taskbar::OnTaskbarLClick(wxTaskBarIconEvent &evt)
{
    wxWindow *f = static_cast<wxWindow*>(Ntab->GetGrandParent());
    f->Show();

}
