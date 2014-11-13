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
#include <map.h>

#define TGridDrawState Gridseh::TGridDrawState

#define NEXT_REC_AFTER_ENTER true
//---------------------------------------------------------------------------
class TEditorBase : public TFrame
{
__published:	// IDE-managed Components
        TEdit *EditText;
        TStaticText *ViewText;
    TEdit *TabInterceptor;
    void __fastcall ViewTextClick(TObject *Sender);
    void __fastcall EditTextKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall EditTextKeyPress(TObject *Sender, char &Key);
    void __fastcall FrameExit(TObject *Sender);
        void __fastcall FrameMouseWheel(TObject *Sender, TShiftState Shift,
          int WheelDelta, TPoint &MousePos, bool &Handled);
    void __fastcall TabInterceptorEnter(TObject *Sender);

private:	// User declarations
    virtual void __fastcall SetParent           (TWinControl* AParent);
    void        __fastcall _RemoveEvents            (TDBGridEh* DBG);
    void        __fastcall _SetupEvents             (TDBGridEh* DBG);
    void        __fastcall EditorBaseDrawColumnCell (TObject *Sender, const TRect &Rect, int DataCol, TColumnEh *Column, TGridDrawState State);
    void        __fastcall EditorBaseKeyPress       (TObject *Sender, char &Key);
    bool        __fastcall isFrameInRect            (TRect &Rect);
    bool        __fastcall isPointInRect            (int X, int Y, TRect &Rect);
    bool        __fastcall isSelectedColumnOutOfRange(TDBGridEh* DBG);


    typedef void __fastcall (__closure *TKeyPressEvent)(TObject* Sender, char &Key);
    typedef void __fastcall (__closure *TDrawColumnCellEvent)(TObject* Sender,const TRect &Rect, int DataCol, TColumnEh* Column, TGridDrawState State);
    TKeyPressEvent          oldOnKeyPress;
    TDrawColumnCellEvent    oldOnDrawColumnCell;
    bool __fastcall isEditableField(AnsiString inFieldName);

protected:
    TRect       FrameCell;

public:		// User declarations
    virtual void        __fastcall SetRect      (TRect inRect);
    virtual void __fastcall Show                    ();
    virtual void __fastcall Hide                    ();

                        __fastcall TEditorBase  (TComponent* Owner);
            void        __fastcall SetAlignment (TAlignment al);
            void        __fastcall SetVal       (AnsiString S);
            void        __fastcall myKeyPress   (unsigned char &Key);
            void        __fastcall SetViewMode  ();
    virtual void        __fastcall SetEditMode  ();
            bool        isEditMode;
    map<AnsiString,bool> listFieldName;
};
//---------------------------------------------------------------------------
extern PACKAGE TEditorBase *EditorBase;
//---------------------------------------------------------------------------
#endif
