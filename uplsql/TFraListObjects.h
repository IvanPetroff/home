//---------------------------------------------------------------------------


#ifndef TFraListObjectsH
#define TFraListObjectsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "DBAccess.hpp"
#include "MemDS.hpp"
#include "Ora.hpp"
#include <Db.hpp>
//---------------------------------------------------------------------------
class TFraListObjects : public TFrame
{
__published:	// IDE-managed Components
        TListBox *ListBox1;
private:	// User declarations
public:		// User declarations
        __fastcall TFraListObjects(TComponent* Owner);
        void __fastcall Init(AnsiString objType);
};
//---------------------------------------------------------------------------
extern PACKAGE TFraListObjects *FraListObjects;
//---------------------------------------------------------------------------
#endif
