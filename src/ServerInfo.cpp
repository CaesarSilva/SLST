#include "ServerInfo.h"
wxBEGIN_EVENT_TABLE(ServerInfo,wxFrame)
    EVT_SOCKET(1313, ServerInfo::OnSocketEvent)
    EVT_BUTTON(10106, ServerInfo::OnClick1)
    EVT_BUTTON(10107, ServerInfo::OnClick2)
wxEND_EVENT_TABLE()

ServerInfo::ServerInfo(wxWindow *parent,
                       wxWindowID id,
                       std::string ipport):wxFrame(nullptr, wxID_ANY, "SLST",wxPoint(30,30),wxSize(500,700))
{
    ip = ipport.substr(0,ipport.find(":"));
    port = ipport.substr(ipport.find(":")+1,ipport.length());
    //rm_test_textctrl = new wxTextCtrl(this,wxID_ANY, wxEmptyString, wxPoint(30,210),wxSize(400,400),wxTE_MULTILINE);

    //Title = new wxStaticText(this, wxID_ANY, port, wxPoint(45,5));
    wxStaticText * rm_Test = new wxStaticText(this, wxID_ANY, ip, wxPoint(77,33));
    wxStaticText * rm_Test1 = new wxStaticText(this, wxID_ANY, port, wxPoint(77,63));
    //RequestServerInformation(ip,port,false);
    requestGamestats(ip,port);
    Show();
    bt_Click1 = new wxButton(this, 10106, "Run Soldat", wxPoint(20,85), wxSize(60,20));
    bt_Click2 = new wxButton(this, 10107, "Run Soldat\n alternative", wxPoint(90,85), wxSize(60,20));
    INIReader reader("./config.ini");

    if (reader.ParseError() != 0)
    {
        std::cout << "Can't load 'test.ini'\n";

    }
    else
    {
        s1path = reader.Get("paths", "soldatpath1", "") ;
        s2path = reader.Get("paths", "soldatpath2", "") ;

    }



    //ctor
}
void ServerInfo::RequestServerInformation(std::string Ip, std::string Port, bool players)
{
    wxHTTP get;
    get.SetHeader(_T("Content-type"), _T("text/html; charset=utf-8"));
    get.SetTimeout(10);
    while (!get.Connect(_T("api.soldat.pl")))  // only the server, no pages here yet ...
        wxSleep(5);
    wxApp::IsMainLoopRunning();
    std::string mystring = std::string("/v0/server/")+Ip+"/"+Port;
    wxInputStream *httpStream = get.GetInputStream(_T("/v0/server/51.38.132.142/23075"));
    //if (get.GetError() == wxPROTO_NOERR)
    //{
    wxString res;
    wxStringOutputStream out_stream(&res);
    httpStream->Read(out_stream);
    //}
    wxDELETE(httpStream);
    get.Close();
    std::string document = std::string(res.mb_str());


}
void ServerInfo::OnClick1(wxCommandEvent &evt)
{
    if(s1path != "")
    {
        std::string fullpath = s1path+ " -connect " + ip +" " + port;
        std::cout << "Run:" << fullpath;
        wxExecute(fullpath, wxEXEC_ASYNC);
    }
    else
    {
        std::cout << "s2path empty" << std::endl;
    }

}
void ServerInfo::OnClick2(wxCommandEvent &evt)
{
    if(s2path != "")
    {
        std::string fullpath = s2path+ " -connect " + ip +" " + port;
        std::cout << "Run:" << fullpath;
        wxExecute(fullpath, wxEXEC_ASYNC);
    }
    else
    {
        std::cout << "s1path empty" << std::endl;
    }
}

void ServerInfo::OnSocketEvent(wxSocketEvent& event)
{
    std::cout << "SOCKET EVENT" << std::endl;
    wxSocketBase *sockBase = event.GetSocket();
    switch (event.GetSocketEvent())
    {
    case wxSOCKET_CONNECTION:
    {


        std::cout << "CONNECTION" << std::endl;
        //const char *buf1 = "logs/gamestat.txt";
        const char *buf1 = "STARTFILES\r\n";
        unsigned char len  = (unsigned char)(wxStrlen(buf1) + 0);
        wxCharBuffer buf2(wxStrlen(buf1));
        //sclient->Write(&len, 1);
        std::cout << "sclient->Write(&len, 1); " <<sclient->Error()<< std::endl;
        sclient->Write(buf1, len);
        std::cout << "sclient->Write(buf, len); "<<  sclient->Error()<< std::endl;


        const char *buf4 = "logs/gamestat.txt\r\n";
        unsigned char len4  = (unsigned char)(wxStrlen(buf4) + 0);
        std::cout << "sclient->Write(&len, 1); " <<sclient->Error()<< std::endl;
        sclient->Write(buf4, len4);
        std::cout << "sclient->Write(buf, len); "<<  sclient->Error()<< std::endl;

        const char *buf5 = "ENDFILES\r\n";
        unsigned char len5  = (unsigned char)(wxStrlen(buf5) + 0);
        std::cout << "sclient->Write(&len, 1); " <<sclient->Error()<< std::endl;
        sclient->Write(buf5, len5);
        std::cout << "sclient->Write(buf, len); "<<  sclient->Error()<< std::endl;
        /*

                //sclient->Read(buf2.data(), len);
                //std::cout << "Read(buf2.data() "<< sclient->Error() <<std::endl;
                //std::cout << buf2.data() << std::endl ;
                std::cout << "break. connection" << std::endl;
                */
        break;


    }
    case wxSOCKET_LOST :
        std::cout << "Conection lost" << std::endl;

        break;
    case wxSOCKET_INPUT:
    {
        std::cout << "STEP 0 START" << std::endl;
        char buf[256];
        sockBase->Read(buf,12);
        std::cout << "BUF1" << buf << std::endl;
        STEP++;
        std::cout << "STEP 0 END" << std::endl;

        std::cout << "STEP 1 START" << std::endl;
        unsigned char buf2[4];
        sockBase->Read(buf2,4);//4 bytes
        std::cout << "BUF(int)"  << "chars" << (int)buf2[3]<< std::endl;
        std::cout << "BUF(int)"  << "chars2" << (int)buf2[2]<< std::endl;
        //std::cout << "BUF(int)"  << "ATOI" << atoi(buf2)<< std::endl;
        data1 = buf2[3] + buf2[2]*256;
        std::cout << "DATA1=" << data1 << std::endl;
        std::cout << "STEP 1 END" << std::endl;
        STEP++;

        std::cout << "STEP 2 START" << std::endl;
        char buf20[256];
        sockBase->Read(buf20,19);//4 bytes
        std::cout << "BUF" << buf20 << std::endl;
        //data1 = (int)buf2;
        std::cout << "STEP 2 END" << std::endl;
        STEP++;

        std::cout << "STEP 3 START" << std::endl;
        char buf30[4];
        sockBase->Read(buf30,4);
        std::cout << "BUF" << buf30 << "int" << atoi(buf30)<< std::endl;
        //data1 = (int)buf2;
        std::cout << "STEP 3 END" << std::endl;
        STEP++;


        std::cout << "STEP 4 START" << std::endl;
        char  buf40[data1];
        sockBase->Read(buf40,data1);
        std::cout << "BUF" << buf40 << std::endl;
        //wxString mystr(buf40);
        std::string GameStr(buf40);
        //wxStaticText * SERVERINFO = new wxStaticText(this, wxID_ANY, mystr, wxPoint(55,80));
        ParseGamestat(GameStr);
        //rm_test_textctrl->AppendText(mystr);
        //rm_test_textctrl->AppendText(wxString::Format(wxT("Rx: %s \n"),
        //                                 wxString::FromUTF8(buf40, data1)));
        //data1 = (int)buf2;
        std::cout << "STEP 4 END" << std::endl;
        STEP++;


        std::cout << "STEP 5 START" << std::endl;
        char buf50[10];
        sockBase->Read(buf50,10);
        std::cout << "BUF" << buf50 << std::endl;
        //data1 = (int)buf2;
        std::cout << "STEP 5 END" << std::endl;
        STEP++;
        sclient->Close();




        std::cout << "input break" << std::endl;
        break;

    }
    default:
        ;
    }
}
void ServerInfo::updateinfo(std::string doc)
{
    /*rapidjson::Document doc ;
    doc.Parse(document.c_str());
    if(doc["Servers"].IsArray())
    {

    }*/

}
void ServerInfo::requestGamestats(std::string Ip, std::string Port)
{
    sclient = new wxSocketClient();
    sclient->SetEventHandler( *this, 1313);
    sclient->SetNotify(wxSOCKET_CONNECTION_FLAG |
                       wxSOCKET_INPUT_FLAG |
                       wxSOCKET_LOST_FLAG);
    sclient->Notify(true);
    wxIPV4address addr;
    addr.Hostname(Ip);
    addr.Service(std::stoi(Port)+10);//fileserver port = soldat port +10
    sclient->Connect(addr, false);

    //sock->Write(&len, 1);//send the length of the message first



}
void ServerInfo::ParseGamestat(std::string wxstr)
{
    std::vector<std::string>  LineVec;
    std::string remaining = wxstr;
    bool a= true;
    while(a)
    {
        if(remaining.find("\n") != std::string::npos)
        {
            LineVec.push_back(remaining.substr(0,remaining.find("\n")));
            remaining = remaining.substr(remaining.find("\n")+1,remaining.length());
        }
        else a= false;

    }
    std::cout << "second For" << std::endl;
    unsigned int b = 0;
    bool teams = false;
    int playercount = -1;
    player CurrentPlayer;
    for( std::string ii : LineVec)
    {
        std::cout << "2Line:" <<ii<< std::endl;
        if(b==1)
        {
            std::cout << "b==1" << std::endl;
            std::cout << "Players:" <<
                      ii.substr(8,ii.length())
                      << std::endl;

        }
        if(b==2)
        {
            std::cout << "b==1" << std::endl;
            std::cout << "Map:" <<
                      ii.substr(3,ii.length())
                      << std::endl;

        }
        if(b==3)
        {
            std::cout << "gamemode:" <<
                      ii.substr(10,ii.length())
                      << std::endl;

        }
        if(b==4)
        {
            std::cout << "timeleft:" <<
                      ii.substr(10,ii.length())
                      << std::endl;

        }
        if(b==5)
        {
            if(ii.substr(0,2)=="Pl")
            {
                std::cout << "No team" << std::endl;
                playercount = 0;
            }
            else
            {
                std::cout << "Team detected" << std::endl;
                teams= true;
            }

        }
        if(teams && (b<9))
        {
            std::cout << "Team" << std::endl;
            if(b==8)
            {
                std::cout << "LASTEAM" << std::endl;

            }
        }
        if(teams && (b==9)) playercount = 0;
        if(playercount == 5)
        {
            CurrentPlayer.Ping = ii;
            playercount=0;
            Players.push_back(CurrentPlayer);

        }
        if(playercount == 4)
        {
            CurrentPlayer.Team = ii;
            playercount++;
        }
        if(playercount == 3)
        {
            CurrentPlayer.Deaths = ii;
            playercount++;
        }
        if(playercount == 2)
        {
            CurrentPlayer.Kills = ii;
            playercount++;
        }
        if(playercount == 1)
        {
            CurrentPlayer.Name = ii;
            playercount++;
        }


        if(playercount == 0) playercount++;


        b++;
    }

    std::cout<<"3rd for, parsing players vector" << std::endl;
    b=0;
    for(player iii :Players)
    {
        std::cout << "Name:"<<
                  iii.Name << "Kills:" <<
                  iii.Kills << "Deaths:" <<
                  iii.Deaths  << "Team:" <<
                  iii.Team << "ping:" <<
                  iii.Ping << std::endl;
        wxStaticText * Nm = new wxStaticText(this, wxID_ANY, iii.Name, wxPoint(20,120+b*15));
        wxStaticText * Kl = new wxStaticText(this, wxID_ANY, iii.Kills, wxPoint(20+120,120+b*15));
        wxStaticText * Dth = new wxStaticText(this, wxID_ANY, iii.Deaths, wxPoint(20+140,120+b*15));
        wxStaticText * Png = new wxStaticText(this, wxID_ANY, iii.Ping, wxPoint(20+160,120+b*15));
        if(iii.Team == "1")
        {
            Nm->SetForegroundColour(wxColour(255,0,0));
            Kl->SetForegroundColour(wxColour(255,0,0));
            Dth->SetForegroundColour(wxColour(255,0,0));
            Png->SetForegroundColour(wxColour(255,0,0));
        }
        if(iii.Team == "2")
        {
            Nm->SetForegroundColour(wxColour(0,0,255));
            Kl->SetForegroundColour(wxColour(0,0,255));
            Dth->SetForegroundColour(wxColour(0,0,255));
            Png->SetForegroundColour(wxColour(0,0,255));
        }
        if(iii.Team == "3")
        {
            Nm->SetForegroundColour(wxColour(255,255,0));
            Kl->SetForegroundColour(wxColour(255,255,0));
            Dth->SetForegroundColour(wxColour(255,255,0));
            Png->SetForegroundColour(wxColour(255,255,0));
        }
        if(iii.Team == "4")
        {
            Nm->SetForegroundColour(wxColour(0,255,0));
            Kl->SetForegroundColour(wxColour(0,255,0));
            Dth->SetForegroundColour(wxColour(0,255,0));
            Png->SetForegroundColour(wxColour(0,255,0));
        }
        if(iii.Team == "5")
        {
            Nm->SetForegroundColour(wxColour(255,0,255));
            Kl->SetForegroundColour(wxColour(255,0,255));
            Dth->SetForegroundColour(wxColour(255,0,255));
            Png->SetForegroundColour(wxColour(255,0,255));
        }

        b++;
    }

}
ServerInfo::~ServerInfo()
{
    //dtor
}
