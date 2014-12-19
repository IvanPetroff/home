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
        ,psTable
        ,psTableName
        ,psProcedure
        ,psFunction
        ,psParams
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
    AnsiString TableTypeName;
    AnsiString ProcFuncName;
    void NewWord(AnsiString inWord);
};
//---------------------------------------------------------------------------
#endif
