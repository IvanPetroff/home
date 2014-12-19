//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "test_TProgStruct.h"
#include "TProgStruct.cpp"
#include "TProgStruct.h"
#include "cppunitlite\TestHarness.h"
#include "cppunitlite\TestResultStdErr.h"


//---------------------------------------------------------------------------

#pragma package(smart_init)

TEST( TProgStructure, ObjectShouldBeCreated)
{
    TProgStruct obj;
}


TEST( Init, ObjectShouldBeInitialized)
{
    TProgStruct obj;
    CHECK( obj.MemberList.size()==0);
    CHECK( obj.State==psNone);
}


TEST( NewWord, StateShouldBeObjectTypeExpected)
{
    TProgStruct obj;
    obj.NewWord("CREATE");
    obj.NewWord("OR");
    obj.NewWord("REPLACE");
    CHECK(obj.State == psObjectTypeExpected);
}


TEST( NewWord, ObjectTypeShouldBeDetected)
{
    TProgStruct obj;
    obj.NewWord("CREATE");
    obj.NewWord("OR");
    obj.NewWord("REPLACE");
    obj.NewWord("TYPE");
    obj.NewWord("QWERTY");
    obj.NewWord("AS");
    CHECK(obj.ObjType == "TYPE");
}


TEST( NewWord, ObjectNameShouldBeDetected)
{
    TProgStruct obj;
    obj.NewWord("CREATE");
    obj.NewWord("OR");
    obj.NewWord("REPLACE");
    obj.NewWord("TYPE");
    obj.NewWord("QWERTY");
    obj.NewWord("AS");
    CHECK(obj.ObjName == "QWERTY");
}


TEST( NewWord, ObjectTypeBodyShouldBeDetected)
{
    TProgStruct obj;
    obj.NewWord("CREATE");
    obj.NewWord("OR");
    obj.NewWord("REPLACE");
    obj.NewWord("FORCE");
    obj.NewWord("TYPE");
    obj.NewWord("BODY");
    obj.NewWord("QWERTY");
    obj.NewWord("IS");
    CHECK(obj.ObjType == "TYPE BODY");
}


TEST( NewWord, AsIsExpected)
{
    {
        TProgStruct obj;
        obj.NewWord("CREATE");
        obj.NewWord("OR");
        obj.NewWord("REPLACE");
        obj.NewWord("FORCE");
        obj.NewWord("TYPE");
        obj.NewWord("QWERTY");
        CHECK(obj.State == psNameObj);
    }
    {
        TProgStruct obj;
        obj.NewWord("CREATE");
        obj.NewWord("OR");
        obj.NewWord("REPLACE");
        obj.NewWord("FORCE");
        obj.NewWord("TYPE");
        obj.NewWord("BODY");
        obj.NewWord("QWERTY");
        CHECK(obj.State == psNameObj);
    }
    {
        TProgStruct obj;
        obj.NewWord("CREATE");
        obj.NewWord("OR");
        obj.NewWord("REPLACE");
        obj.NewWord("FORCE");
        obj.NewWord("TYPE");
        obj.NewWord("QWERTY");
        obj.NewWord("UNDER");
        obj.NewWord("QWE");
        CHECK(obj.State == psZag);
    }

}

TEST( NewWord, UnderNameExpected)
{
    {
        TProgStruct obj;
        obj.NewWord("CREATE");
        obj.NewWord("OR");
        obj.NewWord("REPLACE");
        obj.NewWord("FORCE");
        obj.NewWord("TYPE");
        obj.NewWord("QWERTY");
        obj.NewWord("UNDER");
        CHECK(obj.State == psUnder);
    }
}


TEST( NewWord, StateTypeFound)
{
    {
        TProgStruct obj;
        obj.NewWord("CREATE");
        obj.NewWord("OR");
        obj.NewWord("REPLACE");
        obj.NewWord("FORCE");
        obj.NewWord("TYPE");
        CHECK(obj.State == psTypeObj);
    }
}

