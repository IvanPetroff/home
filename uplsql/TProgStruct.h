//---------------------------------------------------------------------------

#ifndef TProgStructH
#define TProgStructH
#include <vector.h>

enum psStates {psNone,
        psMember,
        psProcFunc,
        psObjectTypeExpected,
        psObjectNameExpected,
        psAsIsExpected,
        psUnderNameExpected
        ,psTypeObj
        ,psNameObj
        ,psAsIs
        ,psUnder
        ,psZag
        };


class TProgStruct {
public:
    TProgStruct() {
        State = psNone;
    }

    vector <AnsiString> MemberList;
    psStates State;
    AnsiString ObjName;
    AnsiString ObjType;
    AnsiString UnderObjName;
    void NewWord(AnsiString inWord);
};
//---------------------------------------------------------------------------
#endif
