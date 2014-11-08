//---------------------------------------------------------------------------

#ifndef TEditorGridH
#define TEditorGridH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TEditorBase.h"
#include <Grids.hpp>
#include <vector.h>
#include "MemTableEh.hpp"
#include <Db.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
//---------------------------------------------------------------------------
class TEditorGrid : public TEditorBase
{
__published:	// IDE-managed Components
        TStringGrid *Grid;
        TMemTableEh *MemTableEh1;
        void __fastcall EditTextChange(TObject *Sender);
        void __fastcall EditTextKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall GridDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
        void __fastcall GridKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall GridDblClick(TObject *Sender);
private:	// User declarations
        virtual void __fastcall SetRect(TRect inRect);
        void __fastcall FilterHistory();
public:		// User declarations
        __fastcall TEditorGrid(TComponent* Owner);
        vector<AnsiString> listAvto;
        map<AnsiString,int> History;
    void __fastcall LoadHistoryFromDataset(TDataSet* DS, AnsiString FieldName);
    virtual void __fastcall SetEditMode();

};
//---------------------------------------------------------------------------
extern PACKAGE TEditorGrid *EditorGrid;
//---------------------------------------------------------------------------
#endif
