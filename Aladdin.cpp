#include <wx/wxprec.h>
#include <iostream>
#include <wx/webview.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/filedlg.h>
#include <wx/print.h>
#include <wx/srchctrl.h>
#include <wx/notebook.h>
#include <wx/ribbon/page.h>
#include <wx/fdrepdlg.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif
class MyApp: public wxApp
{
	public:
		virtual bool OnInit();
	};
	
class MyFrame:public wxFrame
{
	public:
		MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);//MyFrame 构造函数
		wxTextCtrl *text;
		wxSearchCtrl *mSearchCtrl;
		wxWebView *mwebview;
		wxString s;
	private:
		void OnExit(wxCommandEvent& event);
		void OnButton(wxCommandEvent& event);
		void OnButton1(wxCommandEvent& event);
		void OnText(wxCommandEvent& event);
		void Onwebview(wxWebViewEvent& event);
		void OnOpen(wxCommandEvent& event);
		void OnPreview(wxCommandEvent& event);
		void OnAbout(wxCommandEvent& event);
		void OnNewTab(wxCommandEvent& event);
		void OnFind(wxCommandEvent& event);
		wxDECLARE_EVENT_TABLE();
	};

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size)
{
//	SetIcon(wxIcon("sample"));   									设置窗口图标
	wxPanel *mpanel = new wxPanel(this,wxID_ANY);
	
	wxBoxSizer *mTB = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *mBox = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *mBtn = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *mtext = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *mSearch = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *mweb = new wxBoxSizer(wxHORIZONTAL);
	
	wxButton *mbutton = new wxButton(mpanel,wxID_OK,wxT("↶"),wxDefaultPosition,wxSize(25,27),wxBORDER_NONE);
	wxButton *mbutton1 = new wxButton(mpanel,70,wxT("↷"),wxDefaultPosition,wxSize(25,27),wxBORDER_NONE);
	
	mBtn->Add(mbutton);
	mBtn->Add(mbutton1);
	text = new wxTextCtrl(mpanel,100,"http://www.baidu.com", wxDefaultPosition,wxDefaultSize,wxTE_PROCESS_ENTER);
	mtext->Add(text,wxEXPAND);
	
	mSearchCtrl = new wxSearchCtrl(mpanel,101,wxEmptyString,wxDefaultPosition,wxSize(200,27));
	mSearchCtrl->ShowCancelButton(mSearchCtrl->Show());
	
	mBtn->Add(mtext,wxEXPAND);
	mSearch->Add(mSearchCtrl);
	mBox->Add(mBtn,wxEXPAND);
	mBox->Add(mSearch,1);

	mTB->Add(mBox);

	mwebview=wxWebView::New(mpanel, 10,"http://www.baidu.com");
	mwebview->EnableHistory(true);
	//mweb->Add(mwebview,1,wxTOP,5);
	mTB->Add(mwebview,1,wxEXPAND|wxTOP,5);
	mpanel->SetSizer(mTB);
	
	
	wxMenu *menuFile = new wxMenu;
	wxMenu *menuEdit = new wxMenu;
	wxMenu *menuView = new wxMenu;
	wxMenu *menuHistory = new wxMenu;
	wxMenu *menuBookmarks = new wxMenu;
	wxMenu *menuTools = new wxMenu;
	wxMenu *menuHelp = new wxMenu;
	wxMenu *menuaview = new wxMenu;
	wxMenu *menuSubMenu = new wxMenu;
	
	menuFile->Append(11,"New Tab\tCtrl+T");
	menuFile->Append(2,"New Window\tCtrl+N");
	menuFile->Append(3,"New Private Window\tCtrl+Shift+P");
	menuFile->Append(14,"Open File...\tCtrl+O");
	menuFile->AppendSeparator();
	menuFile->Append(5,"Save Page As...\tCtrl+S");
	menuFile->Append(6,"Email Link...");
	menuFile->AppendSeparator();
	menuFile->Append(17,"Print Preview");
	menuFile->Append(8,"Print...\tCtrl+P");
	menuFile->AppendSeparator();
	menuFile->Append(9,"Work Offline");
	
	menuEdit->Append(1,"Undo\tCtrl+Z");
	menuEdit->Append(2,"Redo\tCtrl+Shift+Z");
	menuEdit->AppendSeparator();
	menuEdit->Append(3,"Cut\tCtrl+X");
	menuEdit->Append(4,"Copy\tCtrl+C");
	menuEdit->Append(5,"Paste\tCtrl+V");
	menuEdit->Append(6,"Delete\tDel");
	menuEdit->AppendSeparator();
	menuEdit->Append(7,"Select All\tCtrl+A");
	menuEdit->AppendSeparator();
	menuEdit->Append(28,"Find\tCtrl+F");
	menuEdit->AppendSeparator();
	menuEdit->Append(9,"Preferences");
	
	menuView->AppendSubMenu(menuaview,"Toolbars");
	menuView->AppendSubMenu(menuSubMenu,"Sidebar");
	menuView->AppendSeparator();
	menuView->Append(3,"Zoom");
	menuView->Append(4,"Page Style");
	menuView->Append(5,"Text Encoding");
	menuView->Append(6,"Full Screen\tF11");
	menuView->AppendSeparator();
	menuView->Append(7,"Enter Reader View");
	
	menuaview->AppendCheckItem(1,"Menu Bar");
	menuaview->AppendCheckItem(2,"Bookmarks Toolbar");
	menuaview->AppendSeparator();
	menuaview->Append(3,"Customize...");
	
	menuSubMenu->Append(1,"Bookmarks \tCtrl+B");
	menuSubMenu->Append(2,"History \tCtrl+H");
	
	menuHistory->Append(1,"Show All History\tCtrl+Shift+H");
	menuHistory->Append(2,"Clear Recent History...\tCtrl+Shift+Del");
	menuHistory->AppendSeparator();
	menuHistory->Append(3,"Restore Previous Session");
	menuHistory->Append(4,"Recently Closed Tabs");
	menuHistory->Append(5,"Recently Closed Windows");
	menuHistory->AppendSeparator();
	
	menuBookmarks->Append(1,"Show All Bookmarks\tCtrl+Shift+O");
	menuBookmarks->AppendSeparator();
	menuBookmarks->Append(2,"View Pocket List");
	menuBookmarks->AppendSeparator();
	menuBookmarks->Append(3,"Bookmark This Page\tCtrl+D");
	menuBookmarks->Append(4,"Subscribe to This Page...");
	menuBookmarks->AppendSeparator();
	menuBookmarks->Append(5,"Bookmarks Toolbar");
	menuBookmarks->AppendSeparator();
	menuBookmarks->Append(6,"Recently Bookmarked");
	menuBookmarks->AppendSeparator();
	menuBookmarks->Append(7,"Recent Tage");
	
	menuTools->Append(1,"Downloads\tCtrl+Shift+Y");
	menuTools->Append(2,"Add-ons\tCtrl+Shift+A");
	menuTools->Append(3,"Apps");
	menuTools->Append(4,"Sign In To Sync...");
	menuTools->AppendSeparator();
	menuTools->Append(5,"Web Developer");
	menuTools->Append(6,"Page Info\tCtrl+I");
	
	menuHelp->Append(1,"Firefox Help");
	menuHelp->Append(2,"Firefox Tour");
	menuHelp->Append(3,"Keyboard Shortcuts");
	menuHelp->Append(4,"Firefox Health Report");
	menuHelp->Append(5,"Troubleshooting Information");
	menuHelp->Append(6,"Submit Feedback...");
	menuHelp->Append(7,"Restart With Add-ons Disabled...");
	menuHelp->Append(8,"Report Web Forgery...");
	menuHelp->AppendSeparator();
	menuHelp->Append(wxID_ABOUT,"About Firefox");
	
	
	menuFile->Append(wxID_EXIT);
	
	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuEdit, "&Edit");
	menuBar->Append(menuView, "&View");
	menuBar->Append(menuHistory, "&History");
	menuBar->Append(menuBookmarks, "&Bookmarks");
	menuBar->Append(menuTools, "&Tools");
	menuBar->Append(menuHelp, "&Help");
	SetMenuBar(menuBar);
	
	
	}
	
	void MyFrame::OnButton(wxCommandEvent& event)
{
   mwebview->GoBack();
}
	void MyFrame::OnButton1(wxCommandEvent& event)
	{
	mwebview->GoForward();
	}


	void MyFrame::OnText(wxCommandEvent& event)
	{
		s = text->GetValue();
   mwebview->LoadURL(s);
		}
	void MyFrame::OnOpen(wxCommandEvent& event)
	{
		wxFileDialog	mopenFile(this,wxT("文件管理器"),wxT(""),wxT(""),"*.*|*",wxFD_OPEN | wxFD_FILE_MUST_EXIST);
		mopenFile.ShowModal();
		}
		void MyFrame::OnPreview(wxCommandEvent& event)	
		{
			
    }
    void MyFrame::OnNewTab(wxCommandEvent& event)
    {
		wxDialog *mDialog = new wxDialog(this,71,wxT("留云榭"),wxPoint(50,50),wxSize(1024,768));
		mDialog->Show();
		}
    
	void MyFrame::OnAbout(wxCommandEvent& event)
	{
		wxDialog *mDialog = new wxDialog(this,90,wxT("留云榭软件科技有限公司"),wxDefaultPosition,wxSize(320,480));
		mDialog->Show();
		}
	void MyFrame::OnFind(wxCommandEvent& event)
	{
		wxFindReplaceData *mFindData;
		wxFindReplaceDialog *mFind;
		
		mFind->Create(this,mFindData,wxT("搜索"));
		}	
	bool MyApp::OnInit()
	{
		MyFrame *frame = new MyFrame(wxT("东莞留云榭软件科技有限公司"), wxPoint(50,50),wxSize(1024,768));
		frame->CreateToolBar(wxDEFAULT_FRAME_STYLE,wxID_ANY,wxToolBarNameStr);
		frame->CreateStatusBar(1,wxSTB_DEFAULT_STYLE);
		frame->Show(true);
		return true;
		}

	void MyFrame::Onwebview(wxWebViewEvent& event)
	{
		mwebview->LoadURL(event.GetURL());
		}
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
	wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_BUTTON(wxID_OK,MyFrame::OnButton)
	EVT_BUTTON(70,MyFrame::OnButton1)
	EVT_TEXT_ENTER(100,MyFrame::OnText)
	EVT_MENU(14,MyFrame::OnOpen)
	EVT_MENU(17,MyFrame::OnPreview)
	EVT_MENU(11,MyFrame::OnNewTab)
	EVT_MENU(28,MyFrame::OnFind)
	EVT_MENU(wxID_EXIT,MyFrame::OnExit)
	EVT_MENU(wxID_ABOUT,MyFrame::OnAbout)
	EVT_WEBVIEW_NEWWINDOW(10,MyFrame::Onwebview)
	wxEND_EVENT_TABLE()
	wxIMPLEMENT_APP(MyApp);

