//---------------------------------------------------------------------------

#ifndef TMainFormH
#define TMainFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include "MemTableEh.hpp"
#include "TEditorBase.h"
#include "TEditorGrid.h"
#include <Db.hpp>
#include "MemDS.hpp"
#include "VirtualTable.hpp"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
    TMemTableEh *MT2;
        TDataSource *DataSource1;
        TDBGridEh *DBG;
    TIntegerField *MT2id;
    TDateField *MT2dat;
    TStringField *MT2naim;
    TStringField *MT2cat;
    TFloatField *MT2kol;
    TFloatField *MT2cena;
    TFloatField *MT2stoim;
        TEditorGrid *EditorGrid1;
    TEditorGrid *EditorCat;
    TVirtualTable *MT;
    TPanel *Panel1;
    TButton *Button1;
    TButton *Button2;
    TEditorGrid *EditorCurr;
        void __fastcall MT2AfterPost(TDataSet *DataSet);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall MTAfterPost(TDataSet *DataSet);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall MTAfterInsert(TDataSet *DataSet);
private:	// User declarations
    bool isLoadMode;
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
