//---------------------------------------------------------------------------

#ifndef TInplaceEditorBaseH
#define TInplaceEditorBaseH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "THorizont.h"

//---------------------------------------------------------------------------
class TInplaceEditorBase : public TFrame
{
__published:	// IDE-managed Components
private:	// User declarations
    map <AnsiString,AnsiString> _Val;
    bool                        _ReadOnly;
    TColor                      _Color;

    virtual void        __fastcall _FormCloseQuery       (TObject *Sender, bool &CanClose);
    virtual void        __fastcall _FormClose            (TObject *Sender, TCloseAction &Action);
    virtual void        __fastcall _DBG_FindKeyDown      (TObject *Sender, WORD &Key, TShiftState Shift);
    virtual void        __fastcall _FormDeactivate       (TObject *Sender);
    virtual void        __fastcall _FormKeyUp            (TObject *Sender, WORD &Key, TShiftState Shift);
    virtual void        __fastcall _FormKeyDown          (TObject *Sender, WORD &Key, TShiftState Shift);
    virtual void        __fastcall _DBG_FindDblClick     (TObject *Sender);
    virtual void        __fastcall _FormShow             (TObject *Sender);
    void                __fastcall _AddControlIntoPerimeter(TControl* inControl, THorizont &Horizont);
    void                __fastcall _CreateWindowPerimeter(TForm *inForm);

    virtual AnsiString  __fastcall GetVal       (AnsiString ValName)                    { return _Val[ValName.UpperCase()];};
    virtual void        __fastcall SetVal       (AnsiString ValName, AnsiString newVal) { if (_Val[ValName.UpperCase()] != newVal) {isChanging = true; _Val[ValName.UpperCase()] = newVal;}};
    virtual bool        __fastcall GetReadOnly  ()                                      { return _ReadOnly;};
    virtual void        __fastcall SetReadOnly  (bool newReadOnly)                      { _ReadOnly = newReadOnly;};
    virtual TColor      __fastcall GetColor     ()                                      { return _Color;};
    virtual void        __fastcall SetColor     (TColor newColor)                       { _Color = newColor;};

    virtual void        __fastcall Show         (TRect Rect)                            =0;
    virtual void        __fastcall SaveVal      ()                                      =0;
    virtual void        __fastcall LoadVal      ()                                      =0;

protected:
    bool        isChanging;
    bool        _SelectAll;
    TForm       *myWindow;
    void        __fastcall KillForm     ();
    void        __fastcall CreateFormForThisFrame();


public:		// User declarations
    int         ModalResult;
    int         __fastcall ShowModal            (TRect Rect, bool SelectAll=true);
                __fastcall TInplaceEditorBase   (TComponent* Owner);

    __property AnsiString       Val[AnsiString] = {read=GetVal,       write=SetVal};
    __property bool             ReadOnly        = {read=GetReadOnly,  write=SetReadOnly};
    __property TColor           Color           = {read=GetColor,     write=SetColor};
};
//---------------------------------------------------------------------------
extern PACKAGE TInplaceEditorBase *InplaceEditorBase;
//---------------------------------------------------------------------------
#endif
