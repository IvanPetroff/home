#pragma once
#ifndef TtemTraceH
#define TtemTraceH

// ****************************************************************************
// �����, ������� ����� ��������/��������� ��� ������ ����������������� ������
// ****************************************************************************
//#define TEM_TRACE // ��������� ������ �����������

#define TEM_TRACE_FOR // ����������� ������ FOR
//#define TEM_TRACE_WHILE // ����������� ������ WHILE
//#define TEM_TRACE_DOWHILE // ����������� ������ DO-WHILE
#define TEM_TRACE_IF_TRUE // ����������� ������������� ������� ������� IF
#define TEM_TRACE_IF_FALSE // ����������� ������������� ������� ������� IF
#define TEM_TRACE_RETURN // ����������� ��������� ������� �� ������� �� RETURN
#define TEM_TRACE_BREAK // ����������� ��������� ������� �� ������ �� RETURN
#define TEM_TRACE_CONTINUE // ����������� ��������� ����������� ������ �� CONTINUE
#define TEM_TRACE_BEGIN // ����������� ������ � �������, ���������� �������� ������ BEGIN
#define TEM_TRACE_NO_OPERATOR // ���������� �� ���� ������� ���������� ���������� (�������, � �������� ������� ���� ��������� "::operator")
//#define TEM_TRACE_CLEAR_AFTER_SAVE // ������� ���� � ������, ����� ���������� ���������� � ����
//#define TEM_TRACE_INCREMENT_FILENAME // ������������� ������ ���������� ���������� (��� ���������� �����, ����� ���������� ���������� ����� ��� � �������� "0")
#define TEM_TRACE_SHORT_LOG // ���������� ������ ���� (��� ������� � ������ ������)
//#define TEM_TRACE_TIME // ������ � ��� ��������� ����� ��� ������ ������
//#define TEM_TRACE_TO_EVENT // �������� ��� � ������ ������� Builder (ONLINE)

// ****************************************************************************
// ************** �����, � ������� ����� �������� ��������� ******************//
// ****************************************************************************

#define TEM_TRACE_FILE_NAME "log.txt"                   /*��� ����� ����. ���� �� ������� ������ ����, ���� ���������� � ������� �������*/
#define TEM_TRACE_TAB_COUNT 2                           /*����� �������� ��� ��������� ������� ������ ��������*/
//#define TEM_TRACE_UNITS_ONLY "Johny.cpp,treb_sup.cpp"    /*������ ������� ��� ������� ����� �������������� ������� � ���*/
//#define TEM_TRACE_FUNCTIONS_ONLY "TForm1::Button1Click,TForm1::Button2Click" /*������ �������/������� ��� ������� ����� �������������� ������� � ���*/
//#define TEM_TRACE_SAVE_TIME_INTERVAL 1000             /*�������� �������������� ���� (� ������������)*/
//#define TEM_TRACE_SAVE_LINE_INTERVAL 1000             /*�������� �������������� ���� (��� ���������� ��������� ����� �����)*/
#define TEM_TRACE_MAX_LINES 0                           /*������������ ����� ����� � ����. ����������� ������ �������� ���������� ����� ��������� �����*/
#define TEM_TRACE_ON 1                                  /*��������� ����������� �� ������� ���������
                                                        // #define TEM_TRACE_ON 1 - ��������� �����������
                                                        // #define TEM_TRACE_ON 0 - ���������� �����������



//******************************************************************************
//-------------------------------- ������� �������� ----------------------------
//******************************************************************************
// ��� �����: TtemTraceLog.h
// ����������: ������ ����������� ���������� ���������������� ���������
// ������: 1.2
// �����: �������� �.�.
// ����: 19.09.2012
//
// ������ ��������� ��������� ��� (��������) �������� ���������� ��������� ��� ������������ �������.
// ��� ������������ � ���� ��� ���������� ������ ��������� (����� ������� �������������� ��������� ������ ����)
//
// >>> � � � � � � �   � � � � �: >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// ��� ����, ����� ������ ������������ ������-������������ � ������� ������ ������
// ��������� ���������������� ��������� �� ���������.
// ��� ��������� �������� ������ ������, ��������� ��������� ������ ��� ������ ������ "������� ����������".
//
// � ���������� ������, ��� �Ѩ ��� ����������!
//
// ��� ���� ����� ������������� ���������������� �������:
// - ������/���������� ������ (for, while) � ��������� ���������� ������������ � ������ ������� ����������;
// - ��������� (if) � ������� ���������� ���������� ������� (true/false);
// - ������� ���������� ���������� ������ � �������/������� (break, continue, return)
//
//                              /*************************/
//                             /  � � � � � � � � � � �: /
//                            /*************************/
// 1). � ������� ������ (��� ����������� ���������������� ���������)
// ��� ���������� ����� #define TEM_TRACE_WHILE ��� ����� #define TEM_TRACE_DOWHILE
// ����������� �������������� ����� DO - WHILE (������ ������ �����, �� ��-�� ������ ������������)
// ��������� � ���� ������ �� �������������!!!
// ��� ���������� ����� ���������, ���������� � ������ DO-WHILE
// �������� ����� "while", �� ����� "dowhile"
//
// ������:      ��� ����                        ����������� �����
//              --------                        -----------------
//              do {                            do {
//                  ���� �����;                     ���� �����;
//                  ...;                            ...;
//                  ���� �����;                     ���� �����;
//              while (�������);                dowhile (�������);
//
// ����� ����� �����������, ��������� ����� DO-WHILE ���������� ����������
// ��� ���������� ����� #define TEM_TRACE, ���������������� ���� "dowhile"
// ���������� ��������� �������� (��� �������, ��� � ��������� ������������ ���������� #include "TtemTraceLog.h")

// 2). ���� � ������� ������������ ���������� ������� � �������� "Servers", �������� ����� ���
// WordApplication, ExcelQueryTable � ��. ��������,
// ������ ��� ���������� ������� � ���������� ������ TEM_TRACE ����� ���������
// ��������� �������������� ���� (C++ Warning) Office_2K.h(...): W8070 Function should return a value
// � � ����� ���������� ������ (E2228) Too many error or warning messages (������� ����� ��������������)
// � ���������� ���� ������ �� �������������.
// ��� ������� ���� ��������, ���������� ����������, ����� �������
// include "TtemTraceLog.h" ������������� ����� ������� Office2k
// �.�. ���� ���-�� ������������ ������ ��������� #include "Word_2K_SRVR.h"
// ������ include "TtemTraceLog.h" ����� ����������� ����.
// ������ ����� ����������, ����� ���������� � ���������.

//
//
//                     << ������� � � � � � � � � � � >>
//                     ---------------------------------
// ������� ����� (��������� ��������� �� ���������):
// 1. � ������ ������ ����� ��������� ���������� ������������ ���� #include "TtemTraceLog.h"
// 2. ������ ����� TtemTraceLog.h ��������� ������ �����������
//
// ����������� ����� (��������� ����� ����������� ����������� ���������):
// 3. �������������� �������� �������, ������� ����� ������������ � ����� ���������:
//    - BEGIN -- ������������� ��� ������� ������ ��� �������/�������,
//               ������� �����/������ � ������� ����� �������� � ����.
//    - TXT(�����) -- ������������� ��� ������ � ��� ������������� ������.
//                    � �������, ���� ��� ��������� ������ ���������� ��
//                    ������������ ��� ����� ��������� ��� ���,
//                    ��������� � ���� ����� ������� TXT(� ������ ������ �������� ��� �����, ������� ����� ������� � ���)
//    - VAR(���_����������) -- ������������� ��� ������ � ��� �������� �����-���� ���������� ����� ���������
//                             ��������� �� �������� ����������, ������� ��� ����� � ��� ������, ����� ����������� ������� VAR
//    - SAVE -- ������������� ��� ���������� ���� � ���� � ����� ������� ��� ������.
//              ������ �������� � ��������� ������� SAVE � ����������� ��� ���������� � ����
//    - #define TEM_TRACE_ON 0 - ��, ��� ��������� ���� - �� ������ � ���
//    - #define TEM_TRACE_ON 1 - ��, ��� ��������� ���� - ����Ĩ� � ���
//                               ��� ������� ����� ������������ ��� ������� ������
//                               ��� ������ ���������, ����������� ������� ��� ����������.
//                    ����������:
//                               #define TEM_TRACE_ON 0 ��������� ������ ������ ��������� � ���,
//                               � �� ��������� ����������� ���������!!!
//                               ��� ������� ���������� �������� ����������� ��. �. 4.

// 4. ��� ���������� ������ �����������, ���������� ������������� ����� #define TEM_TRACE
//    ���� ����� #define TEM_TRACE ���������� � ���������� ������ �������,
//    �� ��� ������� ���������� ������ ����������� ���������� �������������� ��� ����� ��������� ����� #define TEM_TRACE
//    �������, ���� �� ��������� �����-���� ���������� �����������,
//    ������� ������� �������� ����� #define TEM_TRACE ��������������� � ������ ����� TtemTraceLog.h
//    ����� ���������� ����� #define TEM_TRACE, ������������������� ������
//    ������������� ��������� ������������� �� ��������������� ����
//
// (���� ������� �������� ��������� ��� ����������� ������� 1-4)
//
// *****************************************************************************
// ------------------------- ������� �������� ����� ����������� ----------------
// *****************************************************************************

// #define TEM_TRACE -- �������� �������������� ��� � ����� ���������
//                      ��� ����� ����� �������� ���� ��� � ����� TtemTraceLog.h
//                      ���� � ������ ���� ������ ��������� #define TEM_TRACE ����� #include "TtemTraceLog.h"
//
// #define TEM_TRACE_ON 0 - �������� ��������� ������ ��������� � ���
// #define TEM_TRACE_ON 1 - �������� ���������� ������ ��������� � ���
//
//     /***************************  !!!��������!!! **************************/
//    / ����� TEM_TRACE_ON ��������/��������� ������ ������ ��������� � ���! /
//   /       �� ��� �������������� ��� � ���� ��������� �������!           /
//  /**********************************************************************/
//
// #define TEM_TRACE_FILE_NAME "file_name" -- ����� ��� ����� ��� ������ ����
//
// #define TEM_TRACE_WHILE -- ��������� ����������� ������ WHILE
// #define TEM_TRACE_FOR -- ��������� ����������� ������ FOR
// #define TEM_TRACE_DOWHILE -- ��������� ����������� ������ DO {} WHILE
//
//
// #define TEM_TRACE_BREAK -- ��������� � ��� ������� ���������� ������ �� "break"
// #define TEM_TRACE_CONTINUE -- ��������� � ��� ������� ���������� ����������� ������ �� "continue"
// #define TEM_TRACE_RETURN -- ��������� � ��� ������� ���������� ������ �� ������� �� "return"
//
// #define TEM_TRACE_IF_TRUE -- ��������� � ��� ������� ������������ ������� "if"
//                              (����������� ������ ���� ��������� ����� TRUE)
//
// #define TEM_TRACE_IF_FALSE -- ��������� � ��� ������� �������������� ������� "if"
//                              (����������� ������ ���� ��������� ����� FALSE (���� ���� � ���))
//
//
//
// #define TEM_TRACE_MAX_LINES N -- (��� N>0) �������� ����������� �� ������������ ����� ����� � ����.
//                                 � ���� ����������� N ��������� �����
// #define TEM_TRACE_MAX_LINES 0 -- ��������� �����������
//
// #define TEM_TRACE_SAVE_TIME_INTERVAL N -- (��� N - ����� > 0) ����� �������� ������� � ������������
//                                           ����� ������� ������������ ���������� �������������� ����������
//                                           ������������ ���� � ����
// #define TEM_TRACE_SAVE_LINE_INTERVAL N -- (��� N - ����� > 0) ����� �������� ������������� ������ ������������ ���� � ����
//                                           ����� ������ N ����� ���������������� ����.
// ��� ���������� ����� TEM_TRACE_SAVE_TIME_INTERVAL � TEM_TRACE_SAVE_LINE_INTERVAL -
// ���������� ������������ ���� � ���� ���������� ���� ��� (��� ���������� ������ ���������).
// ��� ���� �� ������������� ���������� ���� � ������ ���������� ���������� ���������!
//
// #define TEM_TRACE_CLEAR_AFTER_SAVE -- ��������� ������ ������� ������������ � ������ ���� ����� ����� ����������
//                                       �������� ������ ��� ���������� ������
//                                       TEM_TRACE_SAVE_TIME_INTERVAL ��� TEM_TRACE_SAVE_LINE_INTERVAL
// #define TEM_TRACE_INCREMENT_FILENAME  -- ��������� ������������� ������ ������������� ������ ����
//                                          �������� ������ ��� ���������� ������
//                                          TEM_TRACE_SAVE_TIME_INTERVAL ��� TEM_TRACE_SAVE_LINE_INTERVAL
//
// #define TEM_TRACE_NO_OPERATOR -- ���������� �� ���� �������, ���������� � ����� ������ - "::operator"
//                                  (�������� ���������� �� ������)
//
// #define TEM_TRACE_TIME -- ���������� � ������ ������� ����, �������� ���������� �������
//                           � ��������� �� ���������� (�� ����� ���� �� ������ 1/64 ���)
//
// #define TEM_TRACE_TO_EVENT -- ����� ���� � ���� ������� Builder (���� View->Debug Windows->Event Log)
//                               ��� ��� ���� ����� ��������� � ������ ONLINE
//                               !!!�������� �������� ������������������!!!
//
// #define TEM_TRACE_SHORT_LOG -- ��������� ������ ���������� ������ ����
//                                (��� �������/������ ������� � ������ ������)
//
// #define TEM_TRACE_TAB_COUNT N -- (��� N>=0) ���������� ����������� ��������-�������� ��� ������ � ����� (�������, ����� � � �.)
//
//#define TEM_TRACE_UNITS_ONLY "������ ������ ����� �������" -- ������ ������(�������) ������� �� ������� �������� � ����� ����
//#define TEM_TRACE_FUNCTIONS_ONLY "������ ������� ����� �������" -- ������ �������� �������, ������� �� ������� �������� � ���� ����
//                                                                   (�������� ������ ���� ������. �������� TForm1::Button1Click)

//
//---------------------------------------------------------------------------

// *****************************************************************************
/* ���� ������� ���� ������� ���� ������� ���� ������� ���� ������� ���� �������
// *****************************************************************************
#include <vcl.h>
#pragma hdrstop

#define TEM_TRACE // �������� ����� �����������
#include "TtemTraceLog.h"  // ���������� ������ �����������


#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{BEGIN  // �������� ���� � ������� ��� ������ ��������� ����� BEGIN
    int I=0;
    TXT(��������������)  // ����� � ��� ������������ �����
    while (I++<3) {
        VAR(I)  //  ����� � ��� �������� ���������� "I"
        if (true); // ������ �������. ��� ������ � ��� � �������� [TRUE]
        if (false); // ������ �������. ��� ������ � ��� � �������� [FALSE]
    }
    if (true||true);  // ������ �������

    for (int I = 0; I < 5; I++) {
        if (I==2) continue;
        if (I>3) break;
    }
}
//---------------------------------------------------------------------------
*/
// *****************************************************************************
/* � ���������� ��������� ��� ����� ���� ���� (����������� ������)
// *****************************************************************************

// � ����� ������ ������ ������ � ���������� ��������� ������� ����� ������ � �����, ��� �������� ���

[   21] TForm1::Button1Click >>                         // ��� �������� ��� BEGIN
[   23]     TForm1::Button1Click [txt] ��������������   // �������� ����� ������������� ������ � ��� TXT(��������������)
[   24]     TForm1::Button1Click [while] (I++<3) >>     // �.�. �������� ����� TEM_TRACE_WHILE, ��������������� ������ ����� � ���� "while" (� ������� ������������ ������� �����)
[   25]         TForm1::Button1Click [var] I=1          // � ��, ��� ����������� ������ �����, �������� � �������������� ��������
[   26]         TForm1::Button1Click [if] (true)[TRUE]
[   25]         TForm1::Button1Click [var] I=2          // ������� � ��� �������� ���������� ���, ��� �� ������ VAR(I)
[   26]         TForm1::Button1Click [if] (true)[TRUE]  // ��������� ������� "if". � ������� ()��������� ������������ ��� ���� �������� � �������. � � ����������[]- ��������� ���������� �������
[   25]         TForm1::Button1Click [var] I=3
[   26]         TForm1::Button1Click [if] (true)[TRUE]
[    0]     TForm1::Button1Click [while] << [3] (0ms)   // ������ ������ �� ����� "while". � ���������� ��������� ������� ����� ������������ �����.
[   28]     TForm1::Button1Click [if] (true||true)      // ��������� ������� "if". � ��������� ������������ ��� ���� �������� � �������
[   30]     TForm1::Button1Click [for] (int I = 0; I < 5; I++) >> �.�. �������� ����� TEM_TRACE_FOR, ��������������� ������ ����� � ���� "for" (� ������� ������������ ������� �����)
[   31]         TForm1::Button1Click [if] (I==2)[FALSE]
[   32]         TForm1::Button1Click [if] (I>3)[FALSE]
[   31]         TForm1::Button1Click [if] (I==2)[FALSE]     // ������������ "if" ������ "for". � ���������� ��������� ��������� ���������� �������
[   32]         TForm1::Button1Click [if] (I>3)[FALSE]
[   31]         TForm1::Button1Click [if] (I==2)[TRUE]
[   31]         TForm1::Button1Click CONTINUE               // �������������� ������������ "continue"
[   31]         TForm1::Button1Click [if] (I==2)[FALSE]
[   32]         TForm1::Button1Click [if] (I>3)[FALSE]
[   31]         TForm1::Button1Click [if] (I==2)[FALSE]
[   32]         TForm1::Button1Click [if] (I>3)[TRUE]
[   32]         TForm1::Button1Click BREAK                  // �������������� ������������ BREAK
[    0]     TForm1::Button1Click [for] (int I = 0; I < 5; I++) << [4] (0ms) // ������ ������ �� ����� "for".
                                                                            // � ���������� []��������� ������� ����� ������������ �����.
                                                                            // � �������() - ����� ����� ������ ����� � ������������ (� ��������� 1/64 ���)

[    0] TForm1::Button1Click << [0] (0ms)                    // ����������� ������� ������ �� �������, ���������� ������� BEGIN
                                                             // � ������� () ������������ ����� ������ ������� � ������������ (� ��������� 1/64 ���)
*/

#ifdef TEM_TRACE
#define TEM_TRACE_VERSION_INFO "1.2.1"
#define TEM_TRACE_DATE_INFO "21.09.2012"

#define lpad(str,len) TtemTraceLog::log_space.SubString(1,len-str.Length())+str
#define rpad(str,len) str+TtemTraceLog::log_space.SubString(1,len-str.Length())
class TtemTraceLog {
private:
public:
    static int PassLineCount; // ����� ����������� � ���� ����� (����������� #define TEM_TRACE_ON 0)
    static int MaxFunctionLength;
    #ifdef TEM_TRACE_FUNCTIONS_ONLY
      static AnsiString FunctionsOnly;
    #endif
    #ifdef TEM_TRACE_UNITS_ONLY
      static AnsiString UnitsOnly;
    #endif

    static AnsiString FileName;
    static AnsiString FilePath;
    static AnsiString FileExt;
    static int indexFileName;

    static AnsiString log_space;
    static TStringList* Log;
    static int DeleteLinesCount;
    #ifdef TEM_TRACE_SAVE_LINE_INTERVAL
      static int lastLineCount;
    #endif
    #ifdef TEM_TRACE_SAVE_TIME_INTERVAL
      static int lastTimeStamp;
    #endif
    #ifdef TEM_TRACE_SHORT_LOG
      static AnsiString lastFunctionName;
    #endif

    TtemTraceLog() {
        if ( TtemTraceLog::Log!=0) return;
        TtemTraceLog::Log=new TStringList;

        FilePath = TEM_TRACE_FILE_NAME;
        FilePath = FilePath.SubString(1, FilePath.LastDelimiter("\\"));
        FileExt = ExtractFileExt(TEM_TRACE_FILE_NAME);
        FileName = ExtractFileName(TEM_TRACE_FILE_NAME);
        FileName = FileName.SubString(1,FileName.Length()-FileExt.Length());
        ShowMessage("��������!\n����� ����������� ����ר�!");
    }
    ~TtemTraceLog() {
        if (TtemTraceLog::Log==0) return;
//        if (TtemTraceLog::Log->Count==0) return;
        if (TtemTraceLog::DeleteLinesCount>0) TtemTraceLog::Log->Insert(0, "��� ��������. ������� " + IntToStr(TtemTraceLog::DeleteLinesCount) + " ������ �����.");

        AnsiString S = "";
        S = S + "����������� ������ ";
#if defined(TEM_TRACE_FOR)||defined(TEM_TRACE_WHILE)||defined(TEM_TRACE_DOWHILE)
        S += "�������� ��� ";
  #ifdef TEM_TRACE_FOR
        S += "[for]";
  #endif
  #ifdef TEM_TRACE_WHILE
        S += "[while]";
  #endif
  #ifdef TEM_TRACE_DOWHILE
        S += "[do-while]";
  #endif
#else
        S += "���������";
#endif
        TtemTraceLog::Log->Insert(0, S);
//        S += "\n";
        S = "����������� ������� [if] ";
#if defined(TEM_TRACE_IF_TRUE)||defined(TEM_TRACE_IF_FALSE)
        S = S + "�������� ��� ����� ";
  #ifdef TEM_TRACE_IF_TRUE
        S = S + "[TRUE]";
  #endif
  #ifdef TEM_TRACE_IF_FALSE
        S = S + "[FALSE]";
  #endif
#else
        S = S + "���������";
#endif
        TtemTraceLog::Log->Insert(0, S);
//        S += "\n";
        S = "����������� (return,break,continue) ";
#if defined(TEM_TRACE_RETURN)||defined(TEM_TRACE_BREAK)||defined(TEM_TRACE_CONTINUE)
        S += "�������� ��� ";
  #ifdef TEM_TRACE_RETURN
        S = S + "[RETURN]";
  #endif
  #ifdef TEM_TRACE_BREAK
        S = S + "[BREAK]";
  #endif
  #ifdef TEM_TRACE_CONTINUE
        S = S + "[CONTINUE]";
  #endif
#else
        S = S + "���������";
#endif
        TtemTraceLog::Log->Insert(0, S);
//        S = S + "\n";
        S = "����������� [BEGIN] ";
#ifdef TEM_TRACE_BEGIN
        S = S + "��������";
#else
        S = S + "���������";
#endif
        TtemTraceLog::Log->Insert(0, S);

#if defined(TEM_TRACE_UNITS_ONLY)||defined(TEM_TRACE_FUNCTIONS_ONLY)
        S = "������������ ������: ";
  #ifdef TEM_TRACE_UNITS_ONLY
        S += "������: (" + String(TEM_TRACE_UNITS_ONLY) + ") ";
  #endif
  #ifdef TEM_TRACE_FUNCTIONS_ONLY
        S += "�������: (" + String(TEM_TRACE_FUNCTIONS_ONLY) + ")";
  #endif
        TtemTraceLog::Log->Insert(0, S);
#endif
//        S += "\n";

//        TtemTraceLog::Log->Insert(0, S);
        TtemTraceLog::Log->Insert(0, "");
        TtemTraceLog::Log->Insert(0, "���������� �� ����������");
        TtemTraceLog::Log->Insert(0, "���� ������ ������� TtemTraceLog.h (������ ["+String(TEM_TRACE_VERSION_INFO)+"] �� "+String(TEM_TRACE_DATE_INFO)+")");
        TtemTraceLog::Log->Add("");
        if (TtemTraceLog::PassLineCount>0) {
            TtemTraceLog::Log->Add( "��������� "+IntToStr(TtemTraceLog::PassLineCount)+" �����...");
        }
        TtemTraceLog::Log->Add("...����� ����...");

        TtemTraceLog::Log->SaveToFile( TEM_TRACE_FILE_NAME );
        delete TtemTraceLog::Log;
        TtemTraceLog::Log = 0;
    }

    __inline static void Add(int flg_on, int inLine, AnsiString inSpaces, AnsiString inFile, AnsiString inFunctionName, AnsiString inOperator) {
        #ifdef TEM_TRACE_UNITS_ONLY
            if ( String(TEM_TRACE_UNITS_ONLY).Pos(ExtractFileName(inFile))==0) return;
        #endif
        #ifdef TEM_TRACE_FUNCTIONS_ONLY
            if ( String(TEM_TRACE_FUNCTIONS_ONLY).Pos(inFunctionName)==0) return;
        #endif
        if ( flg_on != 1) {
            TtemTraceLog::PassLineCount++;
            return;
        }
        if (TtemTraceLog::PassLineCount>0) {
            TtemTraceLog::Log->Add( "��������� "+IntToStr(TtemTraceLog::PassLineCount)+" �����...");
            TtemTraceLog::PassLineCount = 0;
        }
        AnsiString S;

        #ifdef TEM_TRACE_SHORT_LOG
          if (inFunctionName.Length()>MaxFunctionLength) {
              AnsiString delta = rpad(String(""), inFunctionName.Length() - MaxFunctionLength);
              MaxFunctionLength = inFunctionName.Length();
              for (int I = 0; I < TtemTraceLog::Log->Count; I++) {
                  TtemTraceLog::Log->Strings[I] = delta + TtemTraceLog::Log->Strings[I];
              }
          }
          inFunctionName = lpad(inFunctionName, MaxFunctionLength);
          S = inFunctionName + "[" + lpad(String(inLine),5) +"] " + inSpaces + inOperator;
        #else
          S = "[" + lpad(String(inLine),5) +"] " + inSpaces + inFunctionName + inOperator;
        #endif
        TDateTime D = Now().CurrentTime();
        int TimeStamp = DateTimeToTimeStamp( D).Time;

        #ifdef TEM_TRACE_TIME
            S= lpad(D.TimeString(),8) +"."+ rpad(String(TimeStamp%1000),3)+S;
        #endif
        TtemTraceLog::Log->Add( S);

        #ifdef TEM_TRACE_SAVE_TIME_INTERVAL
            if ((TimeStamp - lastTimeStamp)>TEM_TRACE_SAVE_TIME_INTERVAL) {
                TtemTraceLog::SaveLog("�������������� �� ������� ("+String(TEM_TRACE_SAVE_TIME_INTERVAL)+"ms)");
                lastTimeStamp = TimeStamp;
            }
        #endif
        #ifdef TEM_TRACE_SAVE_LINE_INTERVAL
            if ((TtemTraceLog::Log->Count - lastLineCount)>TEM_TRACE_SAVE_LINE_INTERVAL) {
                lastLineCount = TtemTraceLog::Log->Count;
                TtemTraceLog::SaveLog("�������������� �� ���������� "+String(TEM_TRACE_SAVE_LINE_INTERVAL)+ " �����");
            }
        #endif

        while ( (TEM_TRACE_MAX_LINES>0) && (TtemTraceLog::Log->Count > TEM_TRACE_MAX_LINES)) {
            TtemTraceLog::Log->Delete(0);
            TtemTraceLog::DeleteLinesCount++;
        }
        #ifdef TEM_TRACE_TO_EVENT
          OutputDebugString( S.c_str());
        #endif
    }

    static void SaveLog(AnsiString inTXT) {
        TtemTraceLog::Log->Insert(0,inTXT);
        TtemTraceLog::Log->SaveToFile( FilePath+FileName+String(indexFileName)+FileExt );
        TtemTraceLog::Log->Delete(0);
        #ifdef TEM_TRACE_INCREMENT_FILENAME
          indexFileName++;
        #endif
        #ifdef TEM_TRACE_CLEAR_AFTER_SAVE
          TtemTraceLog::Log->Clear();
        #endif
    }


    __inline static int AddInt(  int flgInt, int flg_on, int inLine, AnsiString inSpaces, AnsiString inFile, AnsiString inFunctionName, AnsiString inOperator) {
        #ifdef TEM_TRACE_NO_OPERATOR
        if (inFunctionName.Pos("::operator")>0) return 1;
        #endif
        TtemTraceLog::Add( flg_on, inLine, inSpaces, inFile, inFunctionName, inOperator);
        return 1;
    }
    __inline static bool AddBool(  bool flgBool, int flg_on, int inLine, AnsiString inSpaces, AnsiString inFile, AnsiString inFunctionName, AnsiString inOperator) {
        #ifndef TEM_TRACE_IF_TRUE
            if (flgBool==true) return flgBool;
        #endif
        #ifndef TEM_TRACE_IF_FALSE
            if (flgBool==false) return flgBool;
        #endif
        TtemTraceLog::Add( flg_on, inLine, inSpaces, inFile, inFunctionName, inOperator +String(flgBool?"[TRUE]":"[FALSE]"));
        return flgBool;
    }
};


int TtemTraceLog::PassLineCount=0;
int TtemTraceLog::MaxFunctionLength=0;


#ifdef TEM_TRACE_FUNCTIONS_ONLY
  AnsiString TtemTraceLog::FunctionsOnly = "," + String(TEM_TRACE_FUNCTIONS_ONLY) + ",";
#endif
#ifdef TEM_TRACE_UNITS_ONLY
  AnsiString TtemTraceLog::UnitsOnly = "," + String(TEM_TRACE_UNITS_ONLY) + ",";
#endif


AnsiString TtemTraceLog::FileName="";
AnsiString TtemTraceLog::FilePath="";
AnsiString TtemTraceLog::FileExt="";
int TtemTraceLog::indexFileName=0;
#ifdef TEM_TRACE_SAVE_LINE_INTERVAL
  int TtemTraceLog::lastLineCount=0;
#endif
#ifdef TEM_TRACE_SAVE_TIME_INTERVAL
  int TtemTraceLog::lastTimeStamp=0;
#endif
#ifdef TEM_TRACE_SHORT_LOG
  AnsiString TtemTraceLog::lastFunctionName="";
#endif
AnsiString TtemTraceLog::log_space = "                                                                                                             ";
int TtemTraceLog::DeleteLinesCount=0;
TStringList* TtemTraceLog::Log=0;


class TmySpaceObject {
private:
    int flg_on;
    AnsiString File;
    AnsiString Func;
    AnsiString Operation;
    int TimeBegin;
    int TimeEnd;
public:
    int Counter_one;
    int LoopCounter;
    static AnsiString SSS;
    __inline TmySpaceObject(int inflg_on, int inLine, AnsiString inFile, AnsiString inFunc, AnsiString inOperation) {
        #ifdef TEM_TRACE_SHORT_LOG
          TtemTraceLog::lastFunctionName="";
        #endif
        flg_on = inflg_on;
        Counter_one = 1;
        LoopCounter = 0;
        Func = inFunc;
        File = inFile;
        Operation = inOperation;
//return;
        TtemTraceLog::Add( flg_on, inLine, TmySpaceObject::SSS+" ", inFile, inFunc, inOperation + ">>");

        // ������ ������, ������ ���� ���� ���� �����������
        if (flg_on==1) TmySpaceObject::SSS = TmySpaceObject::SSS + rpad( String(""),TEM_TRACE_TAB_COUNT);
        TimeBegin = DateTimeToTimeStamp( Now()).Time;
    }

    __inline bool IncLoopCounter(bool in) {
        if (in) LoopCounter++;
        return in;
    }

    __inline ~TmySpaceObject() {
        #ifdef TEM_TRACE_SHORT_LOG
          TtemTraceLog::lastFunctionName="";
        #endif
        TimeEnd = DateTimeToTimeStamp( Now()).Time;

        // ������� ������, ������ ���� ��� ���� ����������� ��� ������ ����� (�.�. ���� �� ���� ������ ���� ���������)
        if (flg_on==1) TmySpaceObject::SSS = TmySpaceObject::SSS.SubString(1, TmySpaceObject::SSS.Length()-TEM_TRACE_TAB_COUNT);
        TtemTraceLog::Add( flg_on, 0, TmySpaceObject::SSS+" ", File, Func, Operation+"<< [" + IntToStr(LoopCounter)+"] ("+String(TimeEnd-TimeBegin) + "ms)");
    }
};
AnsiString TmySpaceObject::SSS = "";


TtemTraceLog TtemTraceLog;
#endif

// ������� �������
#ifdef TEM_TRACE
  #define pusto
  #define retch #

#ifdef TEM_TRACE_BEGIN
  #define BEGIN TmySpaceObject mySpaceObject( TEM_TRACE_ON, __LINE__,__FILE__,__FUNC__,"[BEGIN]");
#else
  #define BEGIN  
#endif

  #define END
  #define TXT(txt) TtemTraceLog::Add( TEM_TRACE_ON, __LINE__, TmySpaceObject::SSS+" ",String(__FILE__),String(__FUNC__), String("[txt] ")+#txt);
  #define VAR(X) TtemTraceLog::Add( TEM_TRACE_ON, __LINE__, TmySpaceObject::SSS+" ",String(__FILE__),String(__FUNC__), "[var] "+String(#X)+"="+String(X));


  #define if(X) if pusto ( TtemTraceLog::AddBool( (X),  TEM_TRACE_ON, __LINE__, TmySpaceObject::SSS+" ",String(__FILE__),String(__FUNC__), "[if] ("+String(#X)+")"))
  #ifndef TEM_TRACE_IF_TRUE
    #ifndef TEM_TRACE_IF_FALSE
      #undef if(X)
    #endif
  #endif

  #ifdef TEM_TRACE_WHILE
    #define while(X) if pusto (false){;}else for pusto (TmySpaceObject mySpaceObject( TEM_TRACE_ON, __LINE__,__FILE__,__FUNC__, "[while] ("+String(#X)+")"); mySpaceObject.IncLoopCounter(X); mySpaceObject.Counter_one=1)
  #endif

  #ifdef TEM_TRACE_FOR
    #define for(X) if pusto (false){;}else for pusto (TmySpaceObject mySpaceObject( TEM_TRACE_ON, __LINE__,__FILE__,__FUNC__, "[for] ("+String(#X)+")"); mySpaceObject.Counter_one>0; mySpaceObject.Counter_one--) for pusto (X, mySpaceObject.IncLoopCounter(true))
//    #define for(X) for pusto (TmySpaceObject mySpaceObject( TEM_TRACE_ON, __LINE__,__FILE__,__FUNC__, "[for] ("+String(#X)+")"); mySpaceObject.Counter_one>0; mySpaceObject.Counter_one--) for pusto (X, mySpaceObject.IncLoopCounter(true))
  #endif

  #ifdef TEM_TRACE_RETURN
    #define return while pusto (TtemTraceLog::AddInt( 1,  TEM_TRACE_ON, __LINE__, TmySpaceObject::SSS+" ", String(__FILE__),String(__FUNC__), "RETURN ")) return
  #endif

  #ifdef TEM_TRACE_BREAK
    #define break { TtemTraceLog::AddInt( 1,  TEM_TRACE_ON, __LINE__, TmySpaceObject::SSS+" ",String(__FILE__),String(__FUNC__), "BREAK "); break;}
  #endif

  #ifdef TEM_TRACE_CONTINUE
    #define continue { TtemTraceLog::AddInt( 1,  TEM_TRACE_ON, __LINE__, TmySpaceObject::SSS+" ",String(__FILE__),String(__FUNC__), "CONTINUE "); continue;}
  #endif

  #ifdef TEM_TRACE_DOWHILE
    #define dowhile(X) while pusto (mySpaceObject.IncLoopCounter(X))
    #define do if pusto (false) {;} else for pusto (TmySpaceObject mySpaceObject( TEM_TRACE_ON, __LINE__,String(__FILE__),__FUNC__, "[dowhile] "); mySpaceObject.Counter_one>0; mySpaceObject.Counter_one--) do pusto
  #else
    #define dowhile(X) while pusto (X)
  #endif

  #define SAVE TtemTraceLog::SaveLog("���������� �� ���������� [SAVE] "+String(__FUNC__)+" ["+String(__LINE__)+"]");

  #pragma message("<<<******************* !!! �  �  �  �  �  �  �  � !!! ***************>>>")
  #pragma message("<<<********** � � � � � � �  � � � � �  � � � � � � � � � � �!*******>>>")
  #pragma message("<<<********** � � � � � � �  � � � � �  � � � � � � � � � � �!*******>>>")
  #pragma message("<<<********** � � � � � � �  � � � � �  � � � � � � � � � � �!*******>>>")
#endif


#ifndef TEM_TRACE
  #define pusto
  #define BEGIN
  #define END
  #define TXT(txt)
  #define VAR(txt)
  #define dowhile(X) while pusto (X)
  #define SAVE
#endif

//---------------------------------------------------------------------------
#endif


