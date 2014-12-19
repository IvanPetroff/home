#include "TestResultStdErr.h"
#include "Failure.h"
#include <iostream>


void TestResultStdErr::addFailure (const Failure & failure) 
{
    TestResult::addFailure(failure);
    SetColor(LightRed,Black);

    std::cerr << failure << " in test " << failure.testName.c_str() << std::endl;
    SetColor(LightGray,Black);
}

void TestResultStdErr::endTests ()
{
    TestResult::endTests();
    std::cerr << testCount << " tests run" << std::endl;
    if (failureCount > 0)
        std::cerr << "****** There were " << failureCount << " failures.";
    else {
        SetColor(LightGreen,Black);
        std::cerr << "There were no test failures.";
        SetColor(LightGray,Black);
    }
    std::cerr << "(time: " << secondsElapsed << " s)" << std::endl;
}

