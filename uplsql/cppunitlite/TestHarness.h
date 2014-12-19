#include <stdio.h>
#include<windows.h>
enum ConsoleColor
{
        Black         = 0,
        Blue          = 1,
        Green         = 2,
        Cyan          = 3,
        Red           = 4,
        Magenta       = 5,
        Brown         = 6,
        LightGray     = 7,
        DarkGray      = 8,
        LightBlue     = 9,
        LightGreen    = 10,
        LightCyan     = 11,
        LightRed      = 12,
        LightMagenta  = 13,
        Yellow        = 14,
        White         = 15
};

void SetColor(ConsoleColor text, ConsoleColor background)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

#include "TestResultStdErr.cpp";
#include "Test.cpp";
#include "TestRegistry.cpp";
#include "TestResult.cpp";
#include "TestResultDebugOut.cpp";

#ifndef TESTHARNESS_H
#define TESTHARNESS_H

#include "Test.h"
#include "TestResult.h"
#include "Failure.h"
#include "TestRegistry.h"


#endif

