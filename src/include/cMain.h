#ifndef CMAIN_H
#define CMAIN_H
#include "wx/wx.h"
#include "MainNotebook.h"
#include <wx/notebook.h>
//TODO remove include above when notebook class is created
class cMain : public wxFrame
{
    public:
        cMain();
        ~cMain();
    public:
        wxButton *m_btn = nullptr;
        wxButton *m_btn1 = nullptr;
        wxTextFile tfile ;
        //rm_ means remove, it means that i'm going to remove the var, by replacing it for another thing, or creating an exclusive class for it
        wxNotebook * rm_notebook;
        wxPanel *rm_npage;

        //notebook stuff bellow
         MainNotebook * Notebook = nullptr;

         void OnBt_Click(wxCommandEvent &evt);
         wxDECLARE_EVENT_TABLE();
    protected:

    private:
};

#endif // CMAIN_H
