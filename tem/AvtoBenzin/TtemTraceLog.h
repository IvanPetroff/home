#pragma once
#ifndef TtemTraceH
#define TtemTraceH

// ****************************************************************************
// Опции, которые можно включать/отключать при помощи закомментаривания строки
// ****************************************************************************
//#define TEM_TRACE // Включение режима трассировки

#define TEM_TRACE_FOR // трассировка циклов FOR
//#define TEM_TRACE_WHILE // трассировка циклов WHILE
//#define TEM_TRACE_DOWHILE // трассировка циклов DO-WHILE
#define TEM_TRACE_IF_TRUE // регистрация положительных исходов условий IF
#define TEM_TRACE_IF_FALSE // регистрация отрицательных исходов условий IF
#define TEM_TRACE_RETURN // регистрация досрочных выходов из функций по RETURN
#define TEM_TRACE_BREAK // регистрация досрочных выходов из циклов по RETURN
#define TEM_TRACE_CONTINUE // регистрация досрочных продолжений циклов по CONTINUE
#define TEM_TRACE_BEGIN // регистрация входов в функции, помеченных ключевым словом BEGIN
#define TEM_TRACE_NO_OPERATOR // Исключение из лога функций перегрузки операторов (функций, в названии которых есть подстрока "::operator")
//#define TEM_TRACE_CLEAR_AFTER_SAVE // очистка лога в памяти, после досрочного сохранения в файл
//#define TEM_TRACE_INCREMENT_FILENAME // автонумерация файлов досрочного сохранения (при отключении опции, файлы досрочного сохранения имеют имя с индексом "0")
#define TEM_TRACE_SHORT_LOG // компактная запись лога (имя функции в начале строки)
//#define TEM_TRACE_TIME // писать в лог системное время для каждой строки
//#define TEM_TRACE_TO_EVENT // выводить лог в окошко событий Builder (ONLINE)

// ****************************************************************************
// ************** Опции, у которых можно изменять параметры ******************//
// ****************************************************************************

#define TEM_TRACE_FILE_NAME "log.txt"                   /*Имя файла лога. Если не указать полный путь, файл помещается в текущий каталог*/
#define TEM_TRACE_TAB_COUNT 2                           /*число пробелов для выделения каждого уровня иерархии*/
//#define TEM_TRACE_UNITS_ONLY "Johny.cpp,treb_sup.cpp"    /*список модулей для которых можно регистрировать события в лог*/
//#define TEM_TRACE_FUNCTIONS_ONLY "TForm1::Button1Click,TForm1::Button2Click" /*список функций/методов для которых можно регистрировать события в лог*/
//#define TEM_TRACE_SAVE_TIME_INTERVAL 1000             /*Интервал автосохранения лога (в милисекундах)*/
//#define TEM_TRACE_SAVE_LINE_INTERVAL 1000             /*Интервал автосохранения лога (при достижении заданного числа строк)*/
#define TEM_TRACE_MAX_LINES 0                           /*максимальное число строк в логе. Сохраняется только заданное количество самых последних строк*/
#define TEM_TRACE_ON 1                                  /*включение трассировки на участке программы
                                                        // #define TEM_TRACE_ON 1 - включение трассировки
                                                        // #define TEM_TRACE_ON 0 - ВЫКЛючение трассировки



//******************************************************************************
//-------------------------------- КРАТКОЕ ОПИСАНИЕ ----------------------------
//******************************************************************************
// Имя файла: TtemTraceLog.h
// Назначение: Модуль трассировки исполнения пользовательской программы
// Версия: 1.2
// Автор: Тимченко Е.М.
// Дата: 19.09.2012
//
// Модуль позволяет сохранять лог (протокол) процесса выполнения программы для последующего анализа.
// Лог записывается в файл при завершении работы программы (также имеются дополнительные настройки вывода лога)
//
// >>> Б Ы С Т Р Ы Й   С Т А Р Т: >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Для того, чтобы начать использовать логгер-трассировщик в базоаом режиме работы
// переделка пользовательской программы не требуется.
// Для включения базового режима работы, требуется выполнить первые два пункта правил "краткой Инструкции".
//
// В ПРОСТЕЙШЕМ СЛУЧАЕ, ЭТО ВСЁ ЧТО НЕОБХОДИМО!
//
// При этом будут автоматически регистрироваться события:
// - начало/завершение циклов (for, while) с подсчётом количества срабатываний и общего времени выполнения;
// - ветвления (if) с выводом результата вычисления условия (true/false);
// - команды досрочного завершения циклов и функций/методов (break, continue, return)
//
//                              /*************************/
//                             /  О Г Р А Н И Ч Е Н И Я: /
//                            /*************************/
// 1). В базовом режиме (без модификации пользовательской программы)
// при включенной опции #define TEM_TRACE_WHILE или опции #define TEM_TRACE_DOWHILE
// некорректно обрабатываются циклы DO - WHILE (весьма редкие циклы, но всё-же иногда используемые)
// программа в этом случае не компилируется!!!
// для исключения этого конфликта, достаточно в циклах DO-WHILE
// заменить слово "while", на слово "dowhile"
//
// Пример:      был цикл                        модификация цикла
//              --------                        -----------------
//              do {                            do {
//                  тело цикла;                     тело цикла;
//                  ...;                            ...;
//                  тело цикла;                     тело цикла;
//              while (условие);                dowhile (условие);
//
// После такой модификации, обработка цикла DO-WHILE становится корректной
// При отключении опции #define TEM_TRACE, модифицированный цикл "dowhile"
// продолжает корректно работать (при условии, что в программе присутствует дирректива #include "TtemTraceLog.h")

// 2). Если в проекте используются компоненты Билдера с закладки "Servers", например такие как
// WordApplication, ExcelQueryTable и пр. подобные,
// иногда при компиляции проекта с включенной опцией TEM_TRACE может возникать
// множество предупреждений типа (C++ Warning) Office_2K.h(...): W8070 Function should return a value
// И в конце появляется ошибка (E2228) Too many error or warning messages (слишком много предупреждений)
// В результате чего проект не компилируется.
// Для решения этой проблемы, необходимо проследить, чтобы строчка
// include "TtemTraceLog.h" располагалась после модулей Office2k
// т.е. если где-то присутствует строка наподобие #include "Word_2K_SRVR.h"
// значит include "TtemTraceLog.h" нужно расположить ниже.
// Обычно этого достаточно, чтобы справиться с проблемой.

//
//
//                     << краткая И Н С Т Р У К Ц И Я >>
//                     ---------------------------------
// Базовый режим (переделка программы не требуется):
// 1. в каждый модуль своей программы подключите заголовочный файл #include "TtemTraceLog.h"
// 2. внутри файла TtemTraceLog.h настройте режимы трассировки
//
// Расширенный режим (требуется лёгкая модификация исследуемой программы):
// 3. Дополнительные ключевые команды, которые можно использовать в вашей программе:
//    - BEGIN -- Предназначена для отметки начала тех функций/методов,
//               события входа/выхода в которые нужно отражать в логе.
//    - TXT(текст) -- Предназначена для вывода в лог произвольного текста.
//                    К примеру, если вам требуется узнать выполнялся ли
//                    интересующий вас кусок программы или нет,
//                    Поставьте в этом месте команду TXT(а внутри скобок напишите тот текст, который нужно вывести в лог)
//    - VAR(имя_переменной) -- Предназначена для вывода в лог значения какой-либо переменной вашей программы
//                             Выводится то значение переменной, которое она имела в тот момент, когда встретилась команда VAR
//    - SAVE -- предназначена для сохранения лога в файл в любой удобный вам момент.
//              Просто напишите в программе команду SAVE и накопленный лог сохранится в файл
//    - #define TEM_TRACE_ON 0 - всё, что находится ниже - не попадёт в лог
//    - #define TEM_TRACE_ON 1 - всё, что находится ниже - ПОПАДЁТ в лог
//                               Эти команды можно использовать для пометки только
//                               тех частей программы, трассировка которых вас интересует.
//                    ПРИМЕЧАНИЕ:
//                               #define TEM_TRACE_ON 0 отключает только выдачу сообщений в лог,
//                               а не отключает трассировку полностью!!!
//                               Для полного отключения скриптов трассировки см. п. 4.

// 4. Для ОТКЛючения режима трассировки, достаточно закоментарить опцию #define TEM_TRACE
//    Если опция #define TEM_TRACE определена в нескольких местах проекта,
//    то для полного выключения режима трассировки необходимо закомментарить все места включения опции #define TEM_TRACE
//    Поэтому, если не требуется какой-либо выборочной трассировки,
//    гораздо удобнее включать опцию #define TEM_TRACE непосредственно в начале файла TtemTraceLog.h
//    После ВЫключения опции #define TEM_TRACE, перекомпилированный проект
//    автоматически ПОЛНОСТЬЮ освобождается от трассировочного кода
//
// (ниже приведён фрагмент программы для иллюстрации пунктов 1-4)
//
// *****************************************************************************
// ------------------------- КРАТКОЕ ОПИСАНИЕ ОПЦИЙ ТРАССИРОВКИ ----------------
// *****************************************************************************

// #define TEM_TRACE -- включает трассировочный код в текст программы
//                      эту опцию можно включить один раз в файле TtemTraceLog.h
//                      либо в каждом своём модуле добавлять #define TEM_TRACE перед #include "TtemTraceLog.h"
//
// #define TEM_TRACE_ON 0 - временно выключает выдачу сообщений в лог
// #define TEM_TRACE_ON 1 - ВКЛючает дальнейшую выдачу сообщений в лог
//
//     /***************************  !!!ВНИМАНИЕ!!! **************************/
//    / Опция TEM_TRACE_ON включает/выключает только ЗАПИСЬ сообщений в лог! /
//   /       Но сам трассировочный код в теле программы остаётся!           /
//  /**********************************************************************/
//
// #define TEM_TRACE_FILE_NAME "file_name" -- задаёт имя файла для вывода лога
//
// #define TEM_TRACE_WHILE -- Включение трассировки циклов WHILE
// #define TEM_TRACE_FOR -- Включение трассировки циклов FOR
// #define TEM_TRACE_DOWHILE -- Включение трассировки циклов DO {} WHILE
//
//
// #define TEM_TRACE_BREAK -- включение в лог событий прерывания циклов по "break"
// #define TEM_TRACE_CONTINUE -- включение в лог событий досрочного продолжения циклов по "continue"
// #define TEM_TRACE_RETURN -- включение в лог событий досрочного выхода из функций по "return"
//
// #define TEM_TRACE_IF_TRUE -- включение в лог событий срабатывания условий "if"
//                              (логгируется только факт отработки ветки TRUE)
//
// #define TEM_TRACE_IF_FALSE -- включение в лог событий НЕсрабатывания условий "if"
//                              (логгируется только факт отработки ветки FALSE (даже если её нет))
//
//
//
// #define TEM_TRACE_MAX_LINES N -- (где N>0) включает ограничение на максимальное число строк в логе.
//                                 в логе сохраняется N ПОСЛЕДНИХ строк
// #define TEM_TRACE_MAX_LINES 0 -- отключает ограничение
//
// #define TEM_TRACE_SAVE_TIME_INTERVAL N -- (где N - число > 0) задаёт интервал времени в милисекундах
//                                           через который периодически происходит автоматическое сохранение
//                                           накопленного лога в файл
// #define TEM_TRACE_SAVE_LINE_INTERVAL N -- (где N - число > 0) задаёт интервал периодической записи накопленного лога в файл
//                                           через каждые N строк сгенерированного лога.
// при отсутствии опций TEM_TRACE_SAVE_TIME_INTERVAL и TEM_TRACE_SAVE_LINE_INTERVAL -
// сохранение накопленного лога в файл происходит один раз (при завершении работы программы).
// При этом не гарантируется сохранение лога в случае аварийного завершения программы!
//
// #define TEM_TRACE_CLEAR_AFTER_SAVE -- включение режима очистки накопленного в памяти лога сразу после сохранения
//                                       работает только при включенных опциях
//                                       TEM_TRACE_SAVE_TIME_INTERVAL или TEM_TRACE_SAVE_LINE_INTERVAL
// #define TEM_TRACE_INCREMENT_FILENAME  -- включение автонумерации файлов периодической записи лога
//                                          работает только при включенных опциях
//                                          TEM_TRACE_SAVE_TIME_INTERVAL или TEM_TRACE_SAVE_LINE_INTERVAL
//
// #define TEM_TRACE_NO_OPERATOR -- исключение из лога функций, содержащих в имени строку - "::operator"
//                                  (помогает избавиться от мусора)
//
// #define TEM_TRACE_TIME -- добавление в каждую строчку лога, текущего системного времени
//                           с точночтью до милисекунд (на самом деле не точнее 1/64 сек)
//
// #define TEM_TRACE_TO_EVENT -- Вывод лога в окно событий Builder (Меню View->Debug Windows->Event Log)
//                               лог при этом можно наблюдать в режиме ONLINE
//                               !!!возможно снижение производительности!!!
//
// #define TEM_TRACE_SHORT_LOG -- включение режима компактной записи лога
//                                (имя функции/метода пишется в начале строки)
//
// #define TEM_TRACE_TAB_COUNT N -- (где N>=0) количество добавляющих пробелов-отступов при заходе в блоки (функции, циклы и т п.)
//
//#define TEM_TRACE_UNITS_ONLY "список файлов через запятую" -- список файлов(модулей) события из которых попадают в текст лога
//#define TEM_TRACE_FUNCTIONS_ONLY "список функций через запятую" -- список названий функций, события из которых попадают в тект лога
//                                                                   (Название должно быть полное. Например TForm1::Button1Click)

//
//---------------------------------------------------------------------------

// *****************************************************************************
/* ФАЙЛ ПРИМЕРА ФАЙЛ ПРИМЕРА ФАЙЛ ПРИМЕРА ФАЙЛ ПРИМЕРА ФАЙЛ ПРИМЕРА ФАЙЛ ПРИМЕРА
// *****************************************************************************
#include <vcl.h>
#pragma hdrstop

#define TEM_TRACE // включаем режим трассировки
#include "TtemTraceLog.h"  // подключаем модуль трассировки


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
{BEGIN  // помечаем вход в функцию при помощи ключевого слова BEGIN
    int I=0;
    TXT(трампарампарам)  // пишем в лог произвольный текст
    while (I++<3) {
        VAR(I)  //  пишем в лог значение переменной "I"
        if (true); // просто условие. Оно попадёт в лог с пометкой [TRUE]
        if (false); // просто условие. Оно попадёт в лог с пометкой [FALSE]
    }
    if (true||true);  // просто условие

    for (int I = 0; I < 5; I++) {
        if (I==2) continue;
        if (I>3) break;
    }
}
//---------------------------------------------------------------------------
*/
// *****************************************************************************
/* В РЕЗУЛЬТАТЕ ПОЛУЧИТСЯ ВОТ ТАКОЙ ФАЙЛ ЛОГА (комментарии автора)
// *****************************************************************************

// В самом начале каждой строки в квадратных скобочках пишется номер строки в файле, где сработал лог

[   21] TForm1::Button1Click >>                         // это сработал наш BEGIN
[   23]     TForm1::Button1Click [txt] трампарампарам   // сработал вывод произвольного текста в лог TXT(трампарампарам)
[   24]     TForm1::Button1Click [while] (I++<3) >>     // т.к. включена опция TEM_TRACE_WHILE, зарегистрирован момент входа в цикл "while" (в скобках отображается условие цикла)
[   25]         TForm1::Button1Click [var] I=1          // и всё, что срабатывает внутри цикла, рисуется с дополнительным отступом
[   26]         TForm1::Button1Click [if] (true)[TRUE]
[   25]         TForm1::Button1Click [var] I=2          // выводим в лог значение переменной там, где мы писали VAR(I)
[   26]         TForm1::Button1Click [if] (true)[TRUE]  // сработало условие "if". В КРУГЛЫХ ()скобочках отображается что было написано в условии. А в квадратных[]- результат вычисления условия
[   25]         TForm1::Button1Click [var] I=3
[   26]         TForm1::Button1Click [if] (true)[TRUE]
[    0]     TForm1::Button1Click [while] << [3] (0ms)   // момент ВЫХОДА из цикла "while". В квадратных скобочках указано число срабатываний цикла.
[   28]     TForm1::Button1Click [if] (true||true)      // сработало условие "if". В скобочках отображается что было написано в условии
[   30]     TForm1::Button1Click [for] (int I = 0; I < 5; I++) >> т.к. включена опция TEM_TRACE_FOR, зарегистрирован момент входа в цикл "for" (в скобках отображается условие цикла)
[   31]         TForm1::Button1Click [if] (I==2)[FALSE]
[   32]         TForm1::Button1Click [if] (I>3)[FALSE]
[   31]         TForm1::Button1Click [if] (I==2)[FALSE]     // срабатывание "if" внутри "for". В квадратных скобочках результат вычисления условия
[   32]         TForm1::Button1Click [if] (I>3)[FALSE]
[   31]         TForm1::Button1Click [if] (I==2)[TRUE]
[   31]         TForm1::Button1Click CONTINUE               // регистрируется срабатывание "continue"
[   31]         TForm1::Button1Click [if] (I==2)[FALSE]
[   32]         TForm1::Button1Click [if] (I>3)[FALSE]
[   31]         TForm1::Button1Click [if] (I==2)[FALSE]
[   32]         TForm1::Button1Click [if] (I>3)[TRUE]
[   32]         TForm1::Button1Click BREAK                  // регистрируется срабатывание BREAK
[    0]     TForm1::Button1Click [for] (int I = 0; I < 5; I++) << [4] (0ms) // момент ВЫХОДА из цикла "for".
                                                                            // В квадратных []скобочках указано число срабатываний цикла.
                                                                            // в круглых() - общее время работы цикла в милисекундах (с точностью 1/64 сек)

[    0] TForm1::Button1Click << [0] (0ms)                    // регистрация момента выхода из функции, помеченной флажком BEGIN
                                                             // в круглых () отображается время работы функции в милисекундах (с точностью 1/64 сек)
*/

#ifdef TEM_TRACE
#define TEM_TRACE_VERSION_INFO "1.2.1"
#define TEM_TRACE_DATE_INFO "21.09.2012"

#define lpad(str,len) TtemTraceLog::log_space.SubString(1,len-str.Length())+str
#define rpad(str,len) str+TtemTraceLog::log_space.SubString(1,len-str.Length())
class TtemTraceLog {
private:
public:
    static int PassLineCount; // число пропущенных в логе строк (диррективой #define TEM_TRACE_ON 0)
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
        ShowMessage("Внимание!\nРежим трассировки ВКЛЮЧЁН!");
    }
    ~TtemTraceLog() {
        if (TtemTraceLog::Log==0) return;
//        if (TtemTraceLog::Log->Count==0) return;
        if (TtemTraceLog::DeleteLinesCount>0) TtemTraceLog::Log->Insert(0, "Лог неполный. Удалено " + IntToStr(TtemTraceLog::DeleteLinesCount) + " первых строк.");

        AnsiString S = "";
        S = S + "Трассировка циклов ";
#if defined(TEM_TRACE_FOR)||defined(TEM_TRACE_WHILE)||defined(TEM_TRACE_DOWHILE)
        S += "включена для ";
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
        S += "ВЫКЛЮЧЕНА";
#endif
        TtemTraceLog::Log->Insert(0, S);
//        S += "\n";
        S = "Трассировка условий [if] ";
#if defined(TEM_TRACE_IF_TRUE)||defined(TEM_TRACE_IF_FALSE)
        S = S + "включена для веток ";
  #ifdef TEM_TRACE_IF_TRUE
        S = S + "[TRUE]";
  #endif
  #ifdef TEM_TRACE_IF_FALSE
        S = S + "[FALSE]";
  #endif
#else
        S = S + "ВЫКЛЮЧЕНА";
#endif
        TtemTraceLog::Log->Insert(0, S);
//        S += "\n";
        S = "Трассировка (return,break,continue) ";
#if defined(TEM_TRACE_RETURN)||defined(TEM_TRACE_BREAK)||defined(TEM_TRACE_CONTINUE)
        S += "включена для ";
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
        S = S + "ВЫКЛЮЧЕНА";
#endif
        TtemTraceLog::Log->Insert(0, S);
//        S = S + "\n";
        S = "Трассировка [BEGIN] ";
#ifdef TEM_TRACE_BEGIN
        S = S + "включена";
#else
        S = S + "ВЫКЛЮЧЕНА";
#endif
        TtemTraceLog::Log->Insert(0, S);

#if defined(TEM_TRACE_UNITS_ONLY)||defined(TEM_TRACE_FUNCTIONS_ONLY)
        S = "Трассируются только: ";
  #ifdef TEM_TRACE_UNITS_ONLY
        S += "модули: (" + String(TEM_TRACE_UNITS_ONLY) + ") ";
  #endif
  #ifdef TEM_TRACE_FUNCTIONS_ONLY
        S += "функции: (" + String(TEM_TRACE_FUNCTIONS_ONLY) + ")";
  #endif
        TtemTraceLog::Log->Insert(0, S);
#endif
//        S += "\n";

//        TtemTraceLog::Log->Insert(0, S);
        TtemTraceLog::Log->Insert(0, "");
        TtemTraceLog::Log->Insert(0, "Сохранение по завершению");
        TtemTraceLog::Log->Insert(0, "Файл создан модулем TtemTraceLog.h (версия ["+String(TEM_TRACE_VERSION_INFO)+"] от "+String(TEM_TRACE_DATE_INFO)+")");
        TtemTraceLog::Log->Add("");
        if (TtemTraceLog::PassLineCount>0) {
            TtemTraceLog::Log->Add( "Пропущено "+IntToStr(TtemTraceLog::PassLineCount)+" строк...");
        }
        TtemTraceLog::Log->Add("...конец лога...");

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
            TtemTraceLog::Log->Add( "Пропущено "+IntToStr(TtemTraceLog::PassLineCount)+" строк...");
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
                TtemTraceLog::SaveLog("Автосохранение по времени ("+String(TEM_TRACE_SAVE_TIME_INTERVAL)+"ms)");
                lastTimeStamp = TimeStamp;
            }
        #endif
        #ifdef TEM_TRACE_SAVE_LINE_INTERVAL
            if ((TtemTraceLog::Log->Count - lastLineCount)>TEM_TRACE_SAVE_LINE_INTERVAL) {
                lastLineCount = TtemTraceLog::Log->Count;
                TtemTraceLog::SaveLog("Автосохранение по достижении "+String(TEM_TRACE_SAVE_LINE_INTERVAL)+ " строк");
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

        // делаем отступ, только если есть флаг трассировки
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

        // удаляем отступ, только если был флаг трассировки при начале блока (т.е. если мы этот отступ туда добавляли)
        if (flg_on==1) TmySpaceObject::SSS = TmySpaceObject::SSS.SubString(1, TmySpaceObject::SSS.Length()-TEM_TRACE_TAB_COUNT);
        TtemTraceLog::Add( flg_on, 0, TmySpaceObject::SSS+" ", File, Func, Operation+"<< [" + IntToStr(LoopCounter)+"] ("+String(TimeEnd-TimeBegin) + "ms)");
    }
};
AnsiString TmySpaceObject::SSS = "";


TtemTraceLog TtemTraceLog;
#endif

// макросы отладки
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

  #define SAVE TtemTraceLog::SaveLog("Сохранение по требованию [SAVE] "+String(__FUNC__)+" ["+String(__LINE__)+"]");

  #pragma message("<<<******************* !!! В  Н  И  М  А  Н  И  Е !!! ***************>>>")
  #pragma message("<<<********** В К Л Ю Ч Ё Н  Р Е Ж И М  Т Р А С С И Р О В К И!*******>>>")
  #pragma message("<<<********** В К Л Ю Ч Ё Н  Р Е Ж И М  Т Р А С С И Р О В К И!*******>>>")
  #pragma message("<<<********** В К Л Ю Ч Ё Н  Р Е Ж И М  Т Р А С С И Р О В К И!*******>>>")
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


