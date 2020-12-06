#include "ServerInfo.h"
wxBEGIN_EVENT_TABLE(ServerInfo,wxFrame)
    EVT_SOCKET(1313, ServerInfo::OnSocketEvent)
//    EVT_BUTTON(10105, NotificationTab::rm_TestClick)
wxEND_EVENT_TABLE()

ServerInfo::ServerInfo(wxWindow *parent,
                       wxWindowID id,
                       std::string ipport):wxFrame(nullptr, wxID_ANY, "SLST",wxPoint(30,30),wxSize(500,700))
{
    std::string ip = ipport.substr(0,ipport.find(":"));
    std::string port = ipport.substr(ipport.find(":")+1,ipport.length());
    //rm_test_textctrl = new wxTextCtrl(this,wxID_ANY, wxEmptyString, wxPoint(30,210),wxSize(400,400),wxTE_MULTILINE);

    //Title = new wxStaticText(this, wxID_ANY, port, wxPoint(45,5));
    wxStaticText * rm_Test = new wxStaticText(this, wxID_ANY, ip, wxPoint(77,33));
    wxStaticText * rm_Test1 = new wxStaticText(this, wxID_ANY, port, wxPoint(77,63));
    //RequestServerInformation(ip,port,false);
    requestGamestats(ip,port);
    Show();

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
        if(STEP == 5) //ENDIFLES
        {
            std::cout << "STEP 5 START" << std::endl;
            char buf2[10];
            sockBase->Read(buf2,10);
            std::cout << "BUF" << buf2 << std::endl;
            //data1 = (int)buf2;
            std::cout << "STEP 5 END" << std::endl;
            STEP++;
            sclient->Close();
        }

        if(STEP == 4) //receive data
        {
            std::cout << "STEP 4 START" << std::endl;
            char  buf2[data1];
            sockBase->Read(buf2,data1);
            std::cout << "BUF" << buf2 << std::endl;
            wxString mystr(buf2);
            wxStaticText * SERVERINFO = new wxStaticText(this, wxID_ANY, mystr, wxPoint(55,80));
            //rm_test_textctrl->AppendText(mystr);
            //rm_test_textctrl->AppendText(wxString::Format(wxT("Rx: %s \n"),
                          //                   wxString::FromUTF8(buf2, data1)));
            //data1 = (int)buf2;
            std::cout << "STEP 4 END" << std::endl;
            STEP++;
        }
        if(STEP == 3) //more 4 bytes
        {
            std::cout << "STEP 3 START" << std::endl;
            char buf2[4];
            sockBase->Read(buf2,4);
            std::cout << "BUF" << buf2 << "int" << atoi(buf2)<< std::endl;
            //data1 = (int)buf2;
            std::cout << "STEP 3 END" << std::endl;
            STEP++;
        }
        if(STEP == 2) // file name logs/gamestat.txt
        {
            std::cout << "STEP 2 START" << std::endl;
            char buf2[256];
            sockBase->Read(buf2,19);//4 bytes
            std::cout << "BUF" << buf2 << std::endl;
            //data1 = (int)buf2;
            std::cout << "STEP 2 END" << std::endl;
            STEP++;
        }
        if(STEP == 1) //RECEIVE 4 bytes
        {
            std::cout << "STEP 1 START" << std::endl;
            unsigned char buf2[4];
            sockBase->Read(buf2,4);//4 bytes
            std::cout << "BUF(int)"  << "chars" << (int)buf2[3]<< std::endl;
            data1 = buf2[3];
            std::cout << "STEP 1 END" << std::endl;
            STEP++;
        }
        if(STEP == 0) //receibe STARTFILES
        {
            std::cout << "STEP 0 START" << std::endl;
            char buf[256];
            sockBase->Read(buf,12);
            std::cout << "BUF1" << buf << std::endl;
            STEP++;
            std::cout << "STEP 0 END" << std::endl;
        }

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
ServerInfo::~ServerInfo()
{
    //dtor
}
