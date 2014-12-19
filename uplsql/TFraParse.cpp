//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TFraParse.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFraParse *FraParse;
//---------------------------------------------------------------------------
__fastcall TFraParse::TFraParse(TComponent* Owner)
        : TFrame(Owner)
{
    myWords["CONSTRUCTOR"]      = THiLt(clBlue, TFontStyles() << fsBold);
    myWords["OVERRIDING"]       = THiLt(clBlue, TFontStyles() << fsBold);
    myWords["MEMBER"]           = THiLt(clBlue, TFontStyles() << fsBold);
    myWords["FUNCTION"]         = THiLt(clBlue, TFontStyles() << fsBold);
    myWords["PROCEDURE"]        = THiLt(clBlue, TFontStyles() << fsBold);
    myWords["NULL"]             = THiLt(clBlue, TFontStyles() << fsBold);
    myWords["IS"]               = THiLt(clBlue, TFontStyles() << fsBold);
    myWords["AS"]               = THiLt(clBlue, TFontStyles() << fsBold);
    myWords["SELF"]             = THiLt(clBlue, TFontStyles() << fsBold);
    myWords["NOT"]              = THiLt(clBlue, TFontStyles() << fsBold);
    myWords["OR"]               = THiLt(clBlue, TFontStyles() << fsBold);
    myWords["AND"]              = THiLt(clBlue, TFontStyles() << fsBold);
    myWords["RETURN"]           = THiLt(clBlue, TFontStyles() << fsBold);
    myWords["BEGIN"]            = THiLt(clRed, TFontStyles() << fsBold);
    myWords["END"]              = THiLt(clRed, TFontStyles() << fsBold);
    myWords["LOOP"]             = THiLt(clRed, TFontStyles() << fsBold);
    myWords["IF"]               = THiLt(clRed, TFontStyles() << fsBold);
    myWords["THEN"]             = THiLt(clRed, TFontStyles() << fsBold);
    myWords["ELSE"]             = THiLt(clRed, TFontStyles() << fsBold);
//    myWords["RAISE_APPLICATION_ERROR"] = THiLt(clRed, TFontStyles() << fsBold);
}
//---------------------------------------------------------------------------


void __fastcall TFraParse::ParseText(AnsiString str)
{
	// ищем по списку ключевых слов...

        AnsiString State="";
        enum WordStates {none, member, procedure_function} WordState = none;
        int begWord = 0;
        int endWord = 0;
        AnsiString Symbol = "~'!@#$%^&*()-=+\\|/?,.[]{}\"`;\n\t\r ";
        int length = str.Length();
        char PredCh = 0;
        char Ch = 0;
        for (int I = 0; I < length; I++) {
            bool isWord = false;
            PredCh = Ch;
            Ch = str.c_str()[I];
            if (Symbol.Pos(Ch)==0) {
                isWord = true;
            }
            if (State=="") {
                if (isWord) {
                    begWord = I;
                    State = "WORD";
                    continue;
                }
            }
            if (State=="WORD") {
                if (isWord==false) {
                    endWord = I;
                    State = "";

                    AnsiString myWord = str.SubString(begWord+1, endWord-begWord).UpperCase();
                    map<AnsiString,THiLt>::iterator it = myWords.find(myWord);
                    if (it != myWords.end()) {
                        PaintText(begWord,endWord, it->second.FontColor, it->second.FontStyle);
                    }

                    switch (WordState) {
                      case none :
                        if (myWord=="MEMBER") {
                            WordState = member;
                        }
                      break;
                      case member :
                        if (myWord=="PROCEDURE" || myWord=="FUNCTION") {
                            WordState = procedure_function;
                        }
                      break;
                      case procedure_function :
                        WordState = none;
                        MemberList.push_back(myWord);
                      break;
                    }

                    int tt=0;
                }
//                continue;
            }

                if (Ch=='*' && PredCh=='/') {
                  int x=0;
                }

            if (State=="") {
                if (Ch=='*' && PredCh=='/') {
                    begWord = I-1;
                    State = "COMMENT_BLOCK";
                    continue;
                }
            }
            if (State=="COMMENT_BLOCK") {
                if (Ch=='/' && PredCh=='*') {
                    endWord = I+1;
                    State = "";
                    PaintText(begWord, endWord, clSilver, TFontStyles());
                }
            }
            if (State=="") {
                if (Ch=='-' && PredCh=='-') {
                    begWord = I-1;
                    State = "COMMENT_LINE";
                    continue;
                }
            }
            if (State=="COMMENT_LINE") {
                if (Ch=='\n' ) {
                    endWord = I;
                    State = "";
                    PaintText(begWord, endWord, clSilver, TFontStyles());
                }
                continue;
            }

        }
}