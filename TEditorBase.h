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
        TEdit *EditText;
        TStaticText *ViewText;
    void __fastcall ViewTextClick(TObject *Sender);
    void __fastcall EditTextKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall EditTextKeyPress(TObject *Sender, char &Key);
    void __fastcall FrameExit(TObject *Sender);
        void __fastcall FrameMouseWheel(TObject *Sender, TShiftState Shift,
          int WheelDelta, TPoint &MousePos, bool &Handled);

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
    bool        __fastcall isSelectedColumnOutOfRange(TDBGridEh* DBG);


    typedef void __fastcall (__closure *TKeyPressEvent)(TObject* Sender, char &Key);
    typedef void __fastcall (__closure *TDrawColumnCellEvent)(TObject* Sender,const TRect &Rect, int DataCol, TColumnEh* Column, TGridDrawState State);
    TKeyPressEvent          oldOnKeyPress;
    TDrawColumnCellEvent    oldOnDrawColumnCell;
    TRect       FrameCell;


public:		// User declarations
    virtual void        __fastcall SetRect      (TRect inRect);

                        __fastcall TEditorBase  (TComponent* Owner);
            void        __fastcall SetAlignment (TAlignment al);
            void        __fastcall SetVal       (AnsiString S);
            void        __fastcall myKeyPress   (char &Key);
            void        __fastcall SetViewMode  ();
            void        __fastcall SetEditMode  ();
            bool        isEditMode;
};
//---------------------------------------------------------------------------
extern PACKAGE TEditorBase *EditorBase;
//---------------------------------------------------------------------------
#endif
