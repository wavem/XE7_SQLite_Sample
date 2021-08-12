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

    RefreshQuery();

    FDTable->Active = true;

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

void __fastcall TFormMain::btn_ADDClick(TObject *Sender)
{
	// Pre Return
    if(FDConnection->Connected == false) {
    	PrintMsg(L"There is no Connection");
        return;
    }

	// Common
    UnicodeString tempStr = L"";
    int t_Idx = 0;
    UnicodeString t_ID = L"";
    UnicodeString t_PW = L"";

    // Get Info From Edit
    t_Idx = StrToInt(ed_Idx->Text);
    t_ID = ed_ID->Text;
    t_PW = ed_PW->Text;

    FDTable->Insert();
    FDTable->FieldByName(L"Idx")->AsInteger = t_Idx;
    FDTable->FieldByName(L"ID")->AsString = t_ID;
    FDTable->FieldByName(L"PW")->AsString = t_PW;
	FDTable->Post();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::RefreshQuery() {
	// Pre Return
    if(FDConnection->Connected == false) {
    	PrintMsg(L"There is no Connection");
        return;
    }

    Query->Close();
    Query->Active = true;
    if(Query->Active == false) {
    	PrintMsg(L"Query Fail...");
        return;
    }
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
        Query->Next();
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::btn_RefreshClick(TObject *Sender)
{
	RefreshQuery();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::btn_DELClick(TObject *Sender)
{
	// Pre Return
    if(FDConnection->Connected == false) {
    	PrintMsg(L"There is no Connection");
        return;
    }

    // Common
    int t_Idx = StrToInt(ed_Idx->Text);
	UnicodeString t_SQL = L"";

    // Find Routine
	// Making Query
	t_SQL = L"SELECT * FROM USER_INFO WHERE IDX = '";
	t_SQL += IntToStr(t_Idx);
	t_SQL += L"';";

	// Find User Routine
	Query_USER->SQL->Clear();
	Query_USER->SQL->Text = t_SQL;
	Query_USER->Open();

	if(t_Idx != Query_USER->FieldByName(L"IDX")->AsInteger) {
    	PrintMsg(L"There is no ID");
    	return;
	}

    PrintMsg(L"Find it!");

    t_SQL.sprintf(L"DELETE FROM USER_INFO WHERE IDX = '%d'", t_Idx);
    Query_USER->SQL->Text = t_SQL;
    Query_USER->ExecSQL();
}
//---------------------------------------------------------------------------

