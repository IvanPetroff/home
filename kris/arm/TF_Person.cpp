//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <map.h>
#include "TF_Person.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBAccess"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "MemDS"
#pragma link "Ora"
#pragma link "TF_MDI"
#pragma resource "*.dfm"
TF_Person *F_Person;
//---------------------------------------------------------------------------
__fastcall TF_Person::TF_Person(TComponent* Owner)
    : TF_MDI(Owner)
{
    BasicCaption = "Карточка пациента";
    Caption = BasicCaption;
    PersonID = 0;
}
//---------------------------------------------------------------------------

void __fastcall TF_Person::OpenPersonID(int in_ID)
{
    PersonID = in_ID;
    Q_Person->Close();
    Q_Person->ParamByName("id")->AsInteger = in_ID;
    Q_Person->Open();
    E_FIO->Text = Q_Person->FieldByName("fio")->AsString;
    E_D_BIRTH->Text = Q_Person->FieldByName("d_birth")->AsString;
    E_SEX->Text = Q_Person->FieldByName("sex")->AsString;
    M_ADDR->Lines->Text = Q_Person->FieldByName("addr")->AsString;
//ShowMessage(Q_Person->FieldByName("addr")->AsString);
    E_TEL->Text = Q_Person->FieldByName("tel")->AsString;
    E_EMAIL->Text = Q_Person->FieldByName("email")->AsString;
    E_D_REG->Text = Q_Person->FieldByName("d_reg")->AsString;
    E_DAT->Text = Q_Person->FieldByName("dat")->AsString;

    Caption = BasicCaption + ":   " + E_FIO->Text.UpperCase() + " (" + E_D_BIRTH->Text + " д.р.)";

    Q_Quest_data->Close();
    Q_Quest_data->ParamByName("id")->AsInteger = in_ID;
    Q_Quest_data->Open();
    map<int,AnsiString> ans;
    for (Q_Quest_data->First(); !Q_Quest_data->Eof; Q_Quest_data->Next()) {
        ans[Q_Quest_data->FieldByName("spr_question_id")->AsInteger] = Q_Quest_data->FieldByName("ans")->AsString;
    }

    for (Q_Simptoms->First(); !Q_Simptoms->Eof; Q_Simptoms->Next()) {
        Q_Simptoms->Edit();
        Q_Simptoms->FieldByName("ans")->AsString = ans[Q_Simptoms->FieldByName("id")->AsInteger];
        Q_Simptoms->Post();
    }
    for (Q_Other->First(); !Q_Other->Eof; Q_Other->Next()) {
        Q_Other->Edit();
        Q_Other->FieldByName("ans")->AsString = ans[Q_Other->FieldByName("id")->AsInteger];
        Q_Other->Post();
    }

    Q_Simptoms->First();
    Q_Other->First();
    Q_Person->Close();
    Q_Quest_data->Close();
}

void __fastcall TF_Person::B_EditClick(TObject *Sender)
{
    SetEditMode(true);
}
//---------------------------------------------------------------------------

void __fastcall TF_Person::SetEditMode(bool flg)
{
    E_FIO->ReadOnly = !flg;
    E_D_BIRTH->ReadOnly = !flg;
    E_SEX->ReadOnly = !flg;
    M_ADDR->ReadOnly = !flg;
    E_TEL->ReadOnly = !flg;
    E_EMAIL->ReadOnly = !flg;
    DBG_Simptoms->ReadOnly = !flg;
    DBG_Other->ReadOnly = !flg;
    B_Edit->Enabled = !flg;
    B_Save->Enabled = flg;
    B_Cancel->Enabled = flg;
}

void __fastcall TF_Person::B_CancelClick(TObject *Sender)
{
    if (Q_Simptoms->State == dsEdit) Q_Simptoms->Cancel();
    if (Q_Other->State == dsEdit) Q_Other->Cancel();

    SetEditMode(false);
    OpenPersonID(PersonID);
}
//---------------------------------------------------------------------------

void __fastcall TF_Person::B_SaveClick(TObject *Sender)
{
    if (Q_Simptoms->State == dsEdit) Q_Simptoms->Post();
    if (Q_Other->State == dsEdit) Q_Other->Post();
    SavePersonInfo();

    SetEditMode(false);
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


void __fastcall TF_Person::SavePersonInfo()
{
    AnsiString xmlString = "";
    XML("ROWSET") {
        XML("ROW") {
            XML("FIO") { XML.val = E_FIO->Text;}
            XML("D_BIRTH") { XML.val = E_D_BIRTH->Text;}
            XML("SEX") { XML.val = E_SEX->Text;}
            XML("ADDR") { XML.val = M_ADDR->Lines->Text;}
            XML("TEL") { XML.val = E_TEL->Text;}
            XML("EMAIL") { XML.val = E_EMAIL->Text;}
        }
    }
    AnsiString sPerson = xmlString;
    xmlString = "";
    XML("ROWSET") {
        for (Q_Simptoms->First(); !Q_Simptoms->Eof; Q_Simptoms->Next()) {
            XML("ROW") {
                XML("ID") { XML.val = Q_Simptoms->FieldByName("id")->AsString;}
                XML("ANS") { XML.val = Q_Simptoms->FieldByName("ans")->AsString;}
            }
        }
    }
    AnsiString sSimptoms = xmlString;

    xmlString = "";
    XML("ROWSET") {
        for (Q_Other->First(); !Q_Other->Eof; Q_Other->Next()) {
            XML("ROW") {
                XML("ID") { XML.val = Q_Other->FieldByName("id")->AsString;}
                XML("ANS") { XML.val = Q_Other->FieldByName("ans")->AsString;}
            }
        }
    }
    AnsiString sOther = xmlString;
    std::auto_ptr<TOraQuery> Q(new TOraQuery(0));
    Q->SQL->Text = "begin person_upd(:id, xmltype(:x)); end;";
    Q->Prepare();
    Q->ParamByName("id")->AsInteger = PersonID;
    Q->ParamByName("x")->AsMemo = sPerson;
    Q->ExecSQL();

}

#undef XML(x)
