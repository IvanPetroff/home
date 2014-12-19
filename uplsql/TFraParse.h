//---------------------------------------------------------------------------


#ifndef TFraParseH
#define TFraParseH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <map.h>
#include <vector.h>
//---------------------------------------------------------------------------
class THiLt
{
public:
	TColor FontColor;
	TFontStyles FontStyle;
        THiLt() {}
        THiLt(TColor inColor, TFontStyles inStyle) {
            FontColor = inColor;
            FontStyle = inStyle;
        }
};



class TFraParse : public TFrame
{
__published:	// IDE-managed Components
private:	// User declarations
        virtual void __fastcall PaintText(int begWord, int endWord, TColor inFontColor, TFontStyles inFontStyle)=0;

public:		// User declarations
        __fastcall TFraParse(TComponent* Owner);
        vector <AnsiString> MemberList;
        void __fastcall ParseText(AnsiString str);
        map<AnsiString,THiLt> myWords;
};
//---------------------------------------------------------------------------
extern PACKAGE TFraParse *FraParse;
//---------------------------------------------------------------------------
#endif
 