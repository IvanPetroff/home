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
//---------------------------------------------------------------------------
class TEditorBase : public TFrame
{
__published:	// IDE-managed Components
    TEdit *Edit1;
    TStaticText *StaticText1;
    void __fastcall FrameResize(TObject *Sender);
    void __fastcall StaticText1Click(TObject *Sender);
    void __fastcall Edit1Exit(TObject *Sender);
    void __fastcall Edit1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall Edit1KeyPress(TObject *Sender, char &Key);
private:	// User declarations
    virtual void __fastcall SetParent(TWinControl* AParent);
    void __fastcall EditorBaseKeyPress(TObject *Sender, char &Key);
    void __fastcall SetupEvents(TDBGridEh* DBG);
    void __fastcall RemoveEvents(TDBGridEh* DBG);
    void __fastcall EditorBaseDrawColumnCell(TObject *Sender,
      const TRect &Rect, int DataCol, TColumnEh *Column,
      TGridDrawState State);

public:		// User declarations
    __fastcall TEditorBase(TComponent* Owner);
    void __fastcall SetRect(TRect inRect);
    void __fastcall SetVal(AnsiString S);
    void __fastcall SetAlignment(TAlignment al);
    void __fastcall myKeyPress(char &Key);


};
//---------------------------------------------------------------------------
extern PACKAGE TEditorBase *EditorBase;
//---------------------------------------------------------------------------
#endif
