//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <memory>
#include <map.h>

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBAccess"
#pragma link "MemDS"
#pragma link "Ora"
#pragma link "TFraBase"
#pragma link "TFraPrcFact"
#pragma link "TFraSZ"
#pragma link "TFraFactNew"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
    try {
        std::auto_ptr<TStringList> SL(new TStringList);
        SL->LoadFromFile("c:\\db_asu.txt");
        for (int I = 0; I < SL->Count; I++) {
            if (SL->Strings[I].SubString(1,1)=="#") continue;
            if (SL->Strings[I].UpperCase().Pos("TEM/")==0) continue;
            db->ConnectString = SL->Strings[I];
            break;
        }
        db->Username;
        db->Password;
        db->LoginPrompt = false;
        db->Options->Direct = true;
        Caption = Caption + " [" + db->Server.Trim() + "]";
    }
    catch (...) {
    }
    db->Connected = true;
    std::auto_ptr<TOraQuery> Q(new TOraQuery(0));
    Q->SQL->Text = "ALTER SESSION SET NLS_NUMERIC_CHARACTERS='.,'";
    Q->ExecSQL();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    std::auto_ptr<TOraQuery> Q(new TOraQuery(0));
    Q->SQL->Text = "select class_spreadlist.load_prc_trud#(:flg,:1).getstringval() x from dual";
    Q->Prepare();

    Q->Close();
    Q->ParamByName("flg")->AsString = "F";
    Q->ParamByName("1")->AsString = Edit1->Text;
    Q->Open();
    sFact = Q->FieldByName("x")->AsString;

    Q->Close();
    Q->ParamByName("flg")->AsString = "N";
    Q->ParamByName("1")->AsString = Edit1->Text;
    Q->Open();
    sNorma = Q->FieldByName("x")->AsString;

    sFactMy = sFact;

    RB_NormaClick(0);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
//    FraFactNew1->DS->Close();
//    FraFactNew1->DS->ParamByName("ceh")->AsString = "8";
//    FraFactNew1->DS->ParamByName("d_beg")->AsString = "01-11-2014";
//    FraFactNew1->DS->ParamByName("d_end")->AsString = "01-12-2014";
//    FraFactNew1->DS->Open();

}
//---------------------------------------------------------------------------
class tXML {
private:
  AnsiString SectionName;
  AnsiString* str;
  int begin_pos;
public:
  map<AnsiString,AnsiString> attr;
  AnsiString val;
  int cnt;
  tXML(AnsiString in_SectionName, AnsiString &in_str) {
      str = &in_str;
      begin_pos = str->Length()+1;
      SectionName = in_SectionName;
      val = "";
      cnt = 1;
  }
  ~tXML() {
      *str = *str + normalize(val) + "</" + normalize(SectionName) + ">";
      *str = str->Insert("<"+normalize(SectionName)+str_attr()+">",begin_pos);
  }


  AnsiString ReplaceSubString(AnsiString Str, AnsiString SubStrFind, AnsiString SubStrToReplace) const
  {
      AnsiString out = "";
      while (int X = Str.Pos( SubStrFind)) {
          out = out + Str.SubString(1,X-1) + SubStrToReplace;
          Str = Str.Delete( 1, X -1 + SubStrFind.Length());
      }
      out = out + Str;
      return out;
  }

  AnsiString normalize(AnsiString str) {
      str = ReplaceSubString(str,"&", "&amp;");
      str = ReplaceSubString(str,"\"", "&quot;");
      str = ReplaceSubString(str,"<", "&lt;");
      str = ReplaceSubString(str,">", "&gt;");
      str = ReplaceSubString(str,"'", "&apos;");
      return str;
  }

  AnsiString str_attr() {
      AnsiString out = "";
      for (map<AnsiString,AnsiString>::iterator it=attr.begin(); it!=attr.end(); it++) {
          out = out + " " + normalize(it->first) + "=\"" + normalize(it->second) + "\"";
      }
      return out;
  }
}; 

#define XML(x) if (false); else for (tXML XML(x,xmlString); XML.cnt>0; XML.cnt--)

AnsiString __fastcall TForm1::GetXML()
{
    AnsiString xmlString = "";
    XML("ROWSET") {
        for (FraPrcFact1->DS->First(); !FraPrcFact1->DS->Eof; FraPrcFact1->DS->Next()) {
            XML("ROW") {
                XML("UCH") XML.val = FraPrcFact1->DS->FieldByName("uch")->AsString;
                XML("UNIZAK") XML.val = FraPrcFact1->DS->FieldByName("unizak")->AsString;
                XML("PRC") XML.val = FraPrcFact1->DS->FieldByName("prc")->AsString;
            }
        }
    }
    return xmlString;
}

void __fastcall TForm1::RB_NormaClick(TObject *Sender)
{
    AnsiString S = "";
    if (RB_Norma->Checked) S = sNorma;
    if (RB_Fact->Checked) S = sFact;

    FraPrcFact1->DS->Close();
    FraSZ1->DS->Close();
    FraPrcFact1->DS->ParamByName("x")->AsMemo = S;
    FraSZ1->DS->ParamByName("x")->AsMemo = S;
    FraSZ1->DS->ParamByName("1")->AsString = Edit1->Text;
    FraPrcFact1->DS->Open();
    FraSZ1->DS->Open();

    sFact = GetXML();
}

//---------------------------------------------------------------------------
