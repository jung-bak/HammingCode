// wxWidgets "Hello World" Program


// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include "ErrorDetection.h"
#include "Conversores.h"
#include "hamming.h"

#include <vector>

#include "wx/colordlg.h"
#include "wx/fontdlg.h"
#include "wx/numdlg.h"
#include "wx/aboutdlg.h"

#include "wx/grid.h"
#include "wx/headerctrl.h"
#include "wx/generic/gridctrl.h"
#include "wx/generic/grideditors.h"


class wxGrid;

class HammingCodeApp : public wxApp
{
public:
	virtual bool OnInit();
};
class MyFrame : public wxFrame
{
	wxBoxSizer *parentSizer;
	wxGridSizer *sizer;
	wxGridSizer *gs;
	wxStaticText *binaryLabel;
	wxStaticText *decLabel;
	wxStaticText *hexLabel;
	wxStaticText *bcdLabel;
	long long int binaryNumber;
public:
	MyFrame();
private:
	void OnNewProject(wxCommandEvent &event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

	void UpdateLabels();
};
enum
{
	ID_NEW_PROJECT = 1
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
    std::vector<int> orig {0,1,1,0,0,0,0};
    std::cout<< "Orig:" <<std::endl;
    H.print(orig);
    std::cout<< "Extend:" <<std::endl;
    H.print( H.extend(orig) );
    std::cout<< "Encoded:" <<std::endl;
    H.print( H.encode(orig,0) );


//DECODE
    std::vector<int> input {1,0,0,0,1,1,0,0,1,0,1};
    std::cout<< "Input:" <<std::endl;
    H.print(input);
    std::cout<< "DECODED:" <<std::endl;
    H.print( H.decode(input,0) );
////
////                               0	1	1	0	0	0	0
///                               {1,1,0,0,1,1,0,0,0,0,0}
    std::vector<int> error_input {0,1,0,0,1,1,0,0,0,0,0};
    std::cout<< "Error input :" <<std::endl;
    H.print(error_input);
    std::cout<< "DECODED AND FIXED:" <<std::endl;
    H.print( H.decode(error_input,0) );

//    H.findNParity(error_input,1,0);



//    for (int i = 0; i < 17; ++i) {
//        std::cout<< i << " P2: " << H.isPowerOfTwo(i) <<std::endl;
//    }


	MyFrame *frame = new MyFrame();
	frame->Show(true);
    return true;
}
MyFrame::MyFrame()
		: wxFrame(NULL, wxID_ANY, "Binary App")
{
	wxMenu *menuFile = new wxMenu;
	menuFile->Append(ID_NEW_PROJECT, "&Nuevo proyecto...\tCtrl-N",
					 "Inicia un nuevo proyecto en Binary App");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT, "Salir", L"Sale de la aplicación");
	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT, "Acerca de", L"Muestra los detalles de la aplicación");
	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&Archivo");
	menuBar->Append(menuHelp, "&Ayuda");
	SetMenuBar( menuBar );
	CreateStatusBar();
	SetStatusText("¡Bienvenido a Binary App!");
	Bind(wxEVT_MENU, &MyFrame::OnNewProject, this, ID_NEW_PROJECT);
	Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);


	wxStaticText *label = new wxStaticText(this, wxID_ANY, L"Número binario introducido: ");
	wxStaticText *label1 = new wxStaticText(this, wxID_ANY, L"Número en decimal: ");
	wxStaticText *label2 = new wxStaticText(this, wxID_ANY, L"Número en hexadecimal: ");
	wxStaticText *label3 = new wxStaticText(this, wxID_ANY, L"Número en BCD: ");

	binaryLabel = new wxStaticText(this, wxID_ANY, "");
	decLabel = new wxStaticText(this, wxID_ANY, "");
	hexLabel = new wxStaticText(this, wxID_ANY, "");
	bcdLabel = new wxStaticText(this, wxID_ANY, "");


	parentSizer = new wxBoxSizer(wxVERTICAL);

	parentSizer->AddSpacer(10);


	sizer = new wxGridSizer(4, 2, 0, 0);

	sizer->Add(label, 0, wxEXPAND | wxLEFT, 10);
	sizer->Add(binaryLabel, 0, wxEXPAND);

	sizer->Add(label1, 0,  wxEXPAND | wxLEFT, 10);
	sizer->Add(decLabel, 0, wxEXPAND);

	sizer->Add(label2, 0,  wxEXPAND | wxLEFT, 10);
	sizer->Add(hexLabel, 0, wxEXPAND);

	sizer->Add(label3, 0,  wxEXPAND | wxLEFT, 10);
	sizer->Add(bcdLabel, 0, wxEXPAND);

	parentSizer->Add(sizer);

	parentSizer->AddSpacer(10);


	gs = new wxGridSizer(4, 5, 3, 3);

	gs->Add(new wxButton(this, -1, wxT("Cls")), 0, wxEXPAND);
	gs->Add(new wxButton(this, -1, wxT("Bck")), 0, wxEXPAND);
	gs->Add(new wxStaticText(this, -1, wxT("")), 0, wxEXPAND);
	gs->Add(new wxButton(this, -1, wxT("Close")), 0, wxEXPAND);
	gs->Add(new wxButton(this, -1, wxT("7")), 0, wxEXPAND);
	gs->Add(new wxButton(this, -1, wxT("8")), 0, wxEXPAND);
	gs->Add(new wxButton(this, -1, wxT("9")), 0, wxEXPAND);
	gs->Add(new wxButton(this, -1, wxT("/")), 0, wxEXPAND);
	gs->Add(new wxButton(this, -1, wxT("4")), 0, wxEXPAND);
	gs->Add(new wxButton(this, -1, wxT("5")), 0, wxEXPAND);
	gs->Add(new wxButton(this, -1, wxT("6")), 0, wxEXPAND);
	gs->Add(new wxButton(this, -1, wxT("*")), 0, wxEXPAND);
	gs->Add(new wxButton(this, -1, wxT("1")), 0, wxEXPAND);
	gs->Add(new wxButton(this, -1, wxT("2")), 0, wxEXPAND);
	gs->Add(new wxButton(this, -1, wxT("3")), 0, wxEXPAND);
	gs->Add(new wxButton(this, -1, wxT("-")), 0, wxEXPAND);
	gs->Add(new wxButton(this, -1, wxT("0")), 0, wxEXPAND);
	gs->Add(new wxButton(this, -1, wxT(".")), 0, wxEXPAND);
	gs->Add(new wxButton(this, -1, wxT("=")), 0, wxEXPAND);
	gs->Add(new wxButton(this, -1, wxT("+")), 0, wxEXPAND);

	parentSizer->Add(gs);

	SetSizer(parentSizer);
	Centre();

}
void MyFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}
void MyFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox(L"Esta es una aplicación hecha para el curso EL-3307 Diseño Lógico del Instituto Tecnológico de "
			  "Costa Rica, primer semestre 2019.\n\nEstudiantes:\n• Joseph Vargas\n• Gustavo Segura\n• Jung Bak",
				 "Acerca de Binary App", wxOK | wxICON_INFORMATION);
}
void MyFrame::OnNewProject(wxCommandEvent &event)
{
	wxTextEntryDialog binaryDialog(this, L"Inserte un número binario de hasta 12 bits", "Nuevo proyecto");
	if ( binaryDialog.ShowModal() == wxID_OK ) {

		long long int number;

		if (!binaryDialog.GetValue().ToLongLong(&number) || !ErrorDetection::checkBinary(number)) {
			wxMessageBox(L"El número introducido no es binario.", "Error", wxOK | wxICON_ERROR);
		} else if (!ErrorDetection::lengthCheck(number)) {
			wxMessageBox(L"El número introducido sobrepasa los 12 bits.", "Error", wxOK | wxICON_ERROR);
		} else {
			binaryNumber = number;
			UpdateLabels();
		}
	}
}
void MyFrame::UpdateLabels()
{
	Conversores C;

	binaryLabel->SetLabel(std::to_string(binaryNumber));
	decLabel->SetLabel(std::to_string(C.binary2decimal(binaryNumber)));
	hexLabel->SetLabel(C.decimal2hexa((C.binary2decimal(binaryNumber))));
	bcdLabel->SetLabel(C.decimal2BDC(C.binary2decimal(binaryNumber)));


}
