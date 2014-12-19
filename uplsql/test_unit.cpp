//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "cppunitlite\TestHarness.h"
#include "cppunitlite\TestResultStdErr.h"
#include "TFraParse.cpp"
#include "TFraParse.h"

//#include "test_TProgStruct.cpp"
//---------------------------------------------------------------------------
#pragma argsused
class TlogData {
public:
  int begWord;
  int endWord;
  TColor FontColor;
  TFontStyles FontStyle;
};



class MockTFraParse : public TFraParse {
public:
    __fastcall MockTFraParse(TComponent* Owner): TFraParse(Owner)
    {
    }

    vector <TlogData> vlog;
    virtual void __fastcall PaintText(int begWord, int endWord, TColor inFontColor, TFontStyles inFontStyle) {
        TlogData logData;
        logData.begWord = begWord;
        logData.endWord = endWord;
        logData.FontColor = inFontColor;
        logData.FontStyle = inFontStyle;
        vlog.push_back(logData);
    }
};


TEST( ParseText, LineCommentShouldBeDetected)
{
    std::auto_ptr <MockTFraParse>  obj(new MockTFraParse(0));
    obj->ParseText("line1\n--line2\nline3");
    CHECK(obj->vlog.size()==1);
    CHECK(obj->vlog[0].begWord==6);
    CHECK(obj->vlog[0].endWord==13);
}

TEST( ParseText, BlockCommentShouldBeDetected)
{
    std::auto_ptr <MockTFraParse>  obj(new MockTFraParse(0));
    obj->ParseText("line1\nli/*ne2\nli*/ne3");
    CHECK(obj->vlog.size()==1);
    CHECK(obj->vlog[0].begWord==8);
    CHECK(obj->vlog[0].endWord==18);
}


TEST( ParseText, BlockCommentNotShouldBeDetectedIntoLineComment)
{
    std::auto_ptr <MockTFraParse>  obj(new MockTFraParse(0));
    obj->ParseText("line1\n--li/*ne2\nli*/ne3");
    CHECK(obj->vlog.size()==1);
    CHECK(obj->vlog[0].begWord==6);
    CHECK(obj->vlog[0].endWord==15);
}


TEST( ParseText, LineCommentNotShouldBeDetectedIntoBlockComment)
{
    std::auto_ptr <MockTFraParse>  obj(new MockTFraParse(0));
    obj->ParseText("line1\nli/*n--e2\nli*/ne3");
    CHECK(obj->vlog.size()==1);
    CHECK(obj->vlog[0].begWord==8);
    CHECK(obj->vlog[0].endWord==20);
}


TEST( ParseText, FunctionListShouldBeBuilding)
{
    std::auto_ptr <MockTFraParse>  obj(new MockTFraParse(0));
    obj->ParseText(
"create or replace type body DokBase is\
\
  member procedure Init is\
  begin\
    lib := t_lib;\
    LoadZagDok(null);\
    LoadSodDok(null);\
    null;\
  end;\
  member function Init2 is\
");
    CHECK(obj->MemberList.size()==2);
    CHECK(obj->MemberList[0]=="INIT");
}



int main(int argc, char* argv[])
{
	TestResultStdErr result;
	TestRegistry::runAllTests(result);
        system( "pause");
        return (result.getFailureCount());
        return 0;
}
//---------------------------------------------------------------------------
