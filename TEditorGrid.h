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
//---------------------------------------------------------------------------
class TEditorGrid : public TEditorBase
{
__published:	// IDE-managed Components
        TStringGrid *Grid;
private:	// User declarations
        virtual void __fastcall SetRect(TRect inRect);
public:		// User declarations
        __fastcall TEditorGrid(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TEditorGrid *EditorGrid;
//---------------------------------------------------------------------------
#endif
