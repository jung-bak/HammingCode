// wxWidgets "Hello World" Program


// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#include "ErrorDetection.h"
#include "Conversores.h"
#include "hamming.h"
#include <vector>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif


class HammingCodeApp : public wxApp
{
public:
	virtual bool OnInit();
};
class MyFrame : public wxFrame
{
public:
	MyFrame();
private:
	void OnHello(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
};
enum
{
	ID_Hello = 1
};


wxIMPLEMENT_APP(HammingCodeApp);
bool HammingCodeApp::OnInit()
{
    ErrorDetection ED;
    Conversores C;
    Hamming H;


    std::cout<<"Binary to Decimal :: " << C.binary2decimal(110111111) << std::endl;
    std::cout<<"Decimal to Hexadecimal :: " << C.decimal2hexa(C.binary2decimal(110111111)) << std::endl;
    std::cout<<"Decimal to Binary :: " << C.decimal2binarySTR(15) << std::endl;
    std::cout<<"BCD :: " << C.decimal2BDC(162) << std::endl;
    std::vector<int> vec{10, 20, 30};

//ENCODE
    std::vector<int> orig {0,1,1,0,1,0,0};
    std::cout<< "Orig:" <<std::endl;
    H.print(orig);
    std::cout<< "Extend:" <<std::endl;
    H.print( H.extend(orig) );
    std::cout<< "Encoded:" <<std::endl;
    H.print( H.encode(orig,0) );


//DECODE                    01001101100
    std::vector<int> input {1,0,0,0,1,1,0,0,1,0,1};
    std::cout<< "Input:" <<std::endl;
    H.print(input);
    std::cout<< "DECODED:" <<std::endl;
    H.print( H.decode(input,0) );
////
////                               0,1,1,0,1,0,0 BIN
///                               0,1,0,0,1,1,0,1,1,0,0 HIMMING
/// /                                                 v
    std::vector<int> error_input {0,1,0,0,1,1,0,1,1,0,1};
    std::cout<< "Error input :" <<std::endl;
    H.print(error_input);
    std::cout<< "DECODED AND FIXED:" <<std::endl;
    H.print( H.decode(error_input,0) );
//    std::cout<< "P0:"<<  H.findNParity(error_input,0,0) << std::endl;
//    std::cout<< "P1:"<<  H.findNParity(error_input,1,0) << std::endl;
//    std::cout<< "P2:"<<  H.findNParity(error_input,2,0) << std::endl;
//    std::cout<< "P3:"<<  H.findNParity(error_input,3,0) << std::endl;
    std::cout<< "ERROR INDEX:"<<  H.findError(error_input,0) << std::endl;




//    for (int i = 0; i < 17; ++i) {
//        std::cout<< i << " P2: " << H.isPowerOfTwo(i) <<std::endl;
//    }


    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}
MyFrame::MyFrame()
		: wxFrame(NULL, wxID_ANY, "Hello World")
{
	wxMenu *menuFile = new wxMenu;
	menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
					 "Help string shown in status bar for this menu item");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);
	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);
	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuHelp, "&Help");
	SetMenuBar( menuBar );
	CreateStatusBar();
	SetStatusText("Welcome to wxWidgets!");
	Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
	Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
}
void MyFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}
void MyFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("This is a wxWidgets Hello World example",
				 "About Hello World", wxOK | wxICON_INFORMATION);
}
void MyFrame::OnHello(wxCommandEvent& event)
{
	wxLogMessage("Hello world from wxWidgets!");
}
