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
//---------------------------------------------------------------------------
class TEditorGrid : public TEditorBase
{
__published:	// IDE-managed Components
        TStringGrid *Grid;
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
public:		// User declarations
        __fastcall TEditorGrid(TComponent* Owner);
        vector<AnsiString> listAvto;
};
//---------------------------------------------------------------------------
extern PACKAGE TEditorGrid *EditorGrid;
//---------------------------------------------------------------------------
#endif
