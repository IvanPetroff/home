//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TFraGasPoint.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBAccess"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "MemDS"
#pragma link "Ora"
#pragma link "TEditorBase"
#pragma link "TEditorGrid"
#pragma link "TEditSimple"
#pragma link "TFraBase"
#pragma link "MemTableEh"
#pragma link "TFraTankGasolineList"
#pragma resource "*.dfm"
TFraGasPoint *FraGasPoint;
//---------------------------------------------------------------------------
__fastcall TFraGasPoint::TFraGasPoint(TComponent* Owner)
        : TFraBase(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TFraGasPoint::_CreateMemoryDataset()
{
    MT->CreateDataSet();
    MT->Open();
}

void __fastcall TFraGasPoint::_CreateInplaceEditors()
{
    EditAvto->Parent = DBG_Sod;
    EditAvto->BringToFront();
    EditAvto->listFieldName["AVTO"]=true;

    EditSimple1->Parent = DBG_Sod;
    EditSimple1->BringToFront();
    EditSimple1->listFieldName["KOL_LITRE"] = true;
}

void __fastcall TFraGasPoint::_LoadAvtoIntoHistoryList()
{
    Q_SloAvto->Open();
    EditAvto->LoadHistoryFromDataset(Q_SloAvto,"N_GAI");
}



void __fastcall TFraGasPoint::Init(TOraSession* in_db)
{
    db = in_db;
    Q_Sod->Session = db;
    Q_listBenzin->Session = db;
    Q_SloAvto->Session = db;

    _CreateMemoryDataset();
    _CreateInplaceEditors();
    _LoadAvtoIntoHistoryList();
    this->FraTankGasolineList1->Init(db);
    this->FraTankGasolineList1->Load(E_SklFrom->Text);
}



void __fastcall TFraGasPoint::MTAfterInsert(TDataSet *DataSet)
{
    MT->FieldByName("kod_mat")->AsString = FraTankGasolineList1->CurrentTankKod;
    MT->FieldByName("k_density")->AsString = CB_Dense->Text;
    MT->FieldByName("mestoh")->AsString = FraTankGasolineList1->CurrentTankMestoh;

}
//---------------------------------------------------------------------------

void __fastcall TFraGasPoint::MTBeforeInsert(TDataSet *DataSet)
{
    if (!MT->IsEmpty() && MT->FieldByName("avto")->AsString.Trim().IsEmpty()) {
        Abort();
    }
}
//---------------------------------------------------------------------------


void __fastcall TFraGasPoint::MTBeforePost(TDataSet *DataSet)
{
    MT->FieldByName("kol_kg")->AsFloat = MT->FieldByName("kol_litre")->AsFloat * MT->FieldByName("k_density")->AsFloat;
    MT->FieldByName("dat")->AsDateTime = Now();

}
//---------------------------------------------------------------------------

