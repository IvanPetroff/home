//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <Classes.hpp>
#include <inifiles.hpp>

#pragma hdrstop

#include "TmyRecords.h"

//---------------------------------------------------------------------------
TmyRecords::TmyRecords(TStringGrid* SG, TComboBox* CB)
{
    this->SG = SG;
    this->CB = CB;
    SG->Cells[1][0] = "Èìÿ";
    SG->Cells[2][0] = "Î÷êè";
    Load();
}


TmyRecords::~TmyRecords()
{
    Save();
}

void __fastcall TmyRecords::Load()
{
    TIniFile *F;
    F = new TIniFile( ExtractFilePath( Application->ExeName) + "INIT.INI" );

    for (int I = 0; I < 10; I++) {
        AnsiString sCount = F->ReadString( "MAIN", "Count_"+String(I), "").Trim().UpperCase();
        AnsiString sName = F->ReadString( "MAIN", "Name_"+String(I), "").Trim().UpperCase();
        if (sCount=="") break;
        Val[I] = StrToInt("0"+sCount);
        Name[I] = sName;
    }
    delete F;
}


void __fastcall TmyRecords::Save()
{
    TIniFile *F;
    F = new TIniFile( ExtractFilePath( Application->ExeName) + "INIT.INI" );

    for (int I = 0; I < 10; I++) {
        if (Name[I]=="") break;
        F->WriteString( "MAIN", "Count_"+String(I), Val[I]);
        F->WriteString( "MAIN", "Name_"+String(I), Name[I]);
    }
    delete F;
}



int __fastcall TmyRecords::getVal(int index)
{
    if ((index+1)>=SG->RowCount) return 0;
    return StrToInt("0"+SG->Cells[2][index+1]);
}


void __fastcall TmyRecords::setVal(int index, int val)
{
    while ((index+1)>=SG->RowCount) SG->RowCount++;
    SG->Cells[2][index+1] = String(val);
}


AnsiString __fastcall TmyRecords::getName(int index)
{
    if ((index+1)>=SG->RowCount) return "";
    return SG->Cells[1][index+1];
}


void __fastcall TmyRecords::setName(int index, AnsiString val)
{
    while ((index+1)>=SG->RowCount) SG->RowCount++;
    while ((index)>=CB->Items->Count) CB->Items->Add("");
    SG->Cells[1][index+1] = val;
    CB->Items->Strings[index] = val;
}


#pragma package(smart_init)
