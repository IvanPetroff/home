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
    TButton *Button1;
    TVirtualTable *MT;
    TIntegerField *MTid;
    TDateField *MTdat;
    TStringField *MTnaim;
    TStringField *MTcat;
    TFloatField *MTkol;
    TFloatField *MTcena;
    TFloatField *MTstoim;
    TButton *Button2;
        void __fastcall MT2AfterPost(TDataSet *DataSet);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall MTAfterPost(TDataSet *DataSet);
    void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
