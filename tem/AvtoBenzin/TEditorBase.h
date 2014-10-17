//---------------------------------------------------------------------------


#ifndef TEditorBaseH
#define TEditorBaseH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include <Grids.hpp>

#define TGridDrawState Gridseh::TGridDrawState
//---------------------------------------------------------------------------
class TEditorBase : public TFrame
{
__published:	// IDE-managed Components
    TEdit *Edit1;
    TStaticText *StaticText1;
        TStringGrid *Grid;
    void __fastcall FrameResize(TObject *Sender);
    void __fastcall StaticText1Click(TObject *Sender);
    void __fastcall Edit1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall Edit1KeyPress(TObject *Sender, char &Key);
    void __fastcall FrameExit(TObject *Sender);

private:	// User declarations
    virtual void __fastcall SetParent           (TWinControl* AParent);
    void        __fastcall _RemoveEvents            (TDBGridEh* DBG);
    void        __fastcall _SetupEvents             (TDBGridEh* DBG);
    void        __fastcall EditorBaseDrawColumnCell (TObject *Sender, const TRect &Rect, int DataCol, TColumnEh *Column, TGridDrawState State);
    void        __fastcall EditorBaseKeyPress       (TObject *Sender, char &Key);
    bool        __fastcall isFrameInRect            (TRect &Rect);
    bool        __fastcall isPointInRect            (int X, int Y, TRect &Rect);
    void        __fastcall Show                     ();
    void        __fastcall Hide                     ();

    typedef void __fastcall (__closure *TKeyPressEvent)(TObject* Sender, char &Key);
    typedef void __fastcall (__closure *TDrawColumnCellEvent)(TObject* Sender,const TRect &Rect, int DataCol, TColumnEh* Column, TGridDrawState State);
    TKeyPressEvent          oldOnKeyPress;
    TDrawColumnCellEvent    oldOnDrawColumnCell;
    TRect       FrameCell;


public:		// User declarations
                __fastcall TEditorBase  (TComponent* Owner);
    void        __fastcall SetRect      (TRect inRect);
    void        __fastcall SetAlignment (TAlignment al);
    void        __fastcall SetVal       (AnsiString S);
    void        __fastcall myKeyPress   (char &Key);
    void        __fastcall SetViewMode  ();
    void        __fastcall SetEditMode  ();
    bool        __fastcall isViewMode   ();
};
//---------------------------------------------------------------------------
extern PACKAGE TEditorBase *EditorBase;
//---------------------------------------------------------------------------
#endif
