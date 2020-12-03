#ifndef NOTIFICATIONTAB_H
#define NOTIFICATIONTAB_H
#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/taskbar.h>
#include <wx/notifmsg.h>
#include <wx/textfile.h>
#ifdef __WXGTK210__
    #include <libnotify/notify.h>
#endif // __WXGTK210__
//#include <wx/vector.h>
#include <vector>

//#include "httplib.h"//TODO Remove it if you dont use it
#include "wx/sstream.h"
#include <wx/protocol/http.h>
#include "rapidjson/document.h"
#include <wx/iconloc.h>
//#include "ini.h"//TODO REMOVE UNUSED LIBRARY
#include "INIReader.h"
//#include <wx/fileconf.h>
//wxDECLARE_EVENT(TaskBarIconEvent, wxCommandEvent);
/*
`pkg-config --cflags --libs glib-2.0`
`pkg-config --cflags --libs gdk-pixbuf-2.0`
removed linker flags

*/
class Taskbar : public wxTaskBarIcon
{
    public:
        Taskbar(wxTaskBarIconType iconType = wxTBI_DEFAULT_TYPE)
    :   wxTaskBarIcon(iconType){}
        //virtual ~Taskbar();
        //void OnTaskbarLClick(wxCommandEvent &evt);
        void OnTaskbarLClick(wxTaskBarIconEvent &evt);
        wxDECLARE_EVENT_TABLE();
    protected:
    protected:

    private:
};

class NotificationTab : public wxPanel
{
    public:
        NotificationTab(wxWindow *parent, wxWindowID id);
        virtual ~NotificationTab();
        wxNotificationMessage * NtMsg = new wxNotificationMessage(_("My title"), _("3 players are playing coop\n on rzal servers"));
        wxIconLocation * icl = new wxIconLocation("sample.ico");
        Taskbar *task = new Taskbar(wxTBI_DOCK);//wxTBI_DOCK
        wxTextCtrl * rm_test_textctrl = nullptr;
        wxButton * rmbt = nullptr;
        wxTextFile tfile ;
        wxTimer * m_timer;
        int evtTime ;
//        INIReader reader("./ServersSearch.INI");
        //INIReader reader ;
        void rm_TestClick(wxCommandEvent &evt);
        void onTaskbarEvent(wxCommandEvent &evt);
        void TimerUpdate(wxTimerEvent &evt);
        void LobbySearch();
        void AddNotification(std::string Title, std::string Description , int type);
        void ShowNextNotification();
        void ShowNotification(std::string Title , std::string Description);

    wxDECLARE_EVENT_TABLE();
    struct SvFilters{
        int MinPlayers=0;
        std::string MapList;

    };

    struct SvIniEntry{
        std::string Ip ;
        int Port;
        int id;
        SvFilters Filters;
        std::string Title;
        std::string Description;
    };
    struct SvInfo{
        std::string Name;
        std::string Map;
        unsigned int NumPlayers;

    };
    struct Notification{
        int type ; //1 for lobbysearch event 2 for serversearch
        std::string Title;
        std::string Description;
    };
    std::vector<SvIniEntry> SvEntries;
    std::vector<Notification> Notifications ;
    protected:
    protected:

    private:
};




#endif // NOTIFICATIONTAB_H
