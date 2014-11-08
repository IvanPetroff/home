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
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TMemTableEh *MemTableEh1;
        TDataSource *DataSource1;
        TDBGridEh *DBG;
        TIntegerField *MemTableEh1id;
        TDateField *MemTableEh1dat;
        TStringField *MemTableEh1naim;
        TStringField *MemTableEh1cat;
        TFloatField *MemTableEh1kol;
        TFloatField *MemTableEh1cena;
        TFloatField *MemTableEh1stoim;
        TEditorGrid *EditorGrid1;
private:	// User declarations
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
