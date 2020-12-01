#ifndef MAINNOTEBOOK_H
#define MAINNOTEBOOK_H
#include "wx/wx.h"

#include <wx/notebook.h>
#include "Lobby.h"
#include "NotificationTab.h"

class MainNotebook : public wxNotebook
{
    public:
        MainNotebook(wxWindow *parent, wxWindowID id, const wxPoint pos);
        virtual ~MainNotebook();

    public:

        Lobby * PgLobby = nullptr;
        NotificationTab * PgNotifications = nullptr;
        //variables wit rm_ prefix will be removed, some of them replaced by an exclusive class
        //wxPanel *rm_PgLobby = nullptr;
        wxPanel *rm_PgEditor = nullptr;
    protected:

    private:
};

#endif // MAINNOTEBOOK_H
