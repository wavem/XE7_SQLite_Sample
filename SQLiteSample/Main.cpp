//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvMemo"
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
	: TForm(Owner)
{
	InitProgram();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormClose(TObject *Sender, TCloseAction &Action)
{
	ExitProgram();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::InitProgram() {

    // Connection
    FDConnection->Connected = true;
    if(FDConnection->Connected == false) {
        PrintMsg(L"Can't Connect to DB");
        return;
    }

    Query->Active = true;

    int t_RecordCount = Query->RecordCount;
    UnicodeString tempStr = L"";
    int t_Idx = 0;
    UnicodeString t_ID = L"";
    UnicodeString t_PW = L"";


    tempStr.sprintf(L"Record Count : %d", t_RecordCount);
    PrintMsg(tempStr);

    for(int i = 0 ; i < t_RecordCount ; i++) {
    	t_Idx = Query->FieldByName(L"IDX")->AsInteger;
        t_ID = Query->FieldByName(L"ID")->AsString;
        t_PW = Query->FieldByName(L"PW")->AsString;
        tempStr.sprintf(L"Idx : %d, ID : %s, PW : %s", t_Idx, t_ID.c_str(), t_PW.c_str());
        PrintMsg(tempStr);
    }

    PrintMsg(L"Init Complete");
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ExitProgram() {

}
//---------------------------------------------------------------------------

void __fastcall TFormMain::PrintMsg(UnicodeString _str) {
	int t_Idx =	memo->Lines->Add(_str);
	memo->SetCursor(0, t_Idx);
}
//---------------------------------------------------------------------------

