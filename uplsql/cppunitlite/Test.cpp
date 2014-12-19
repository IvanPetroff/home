

#include "Test.h"
#include "TestRegistry.h"
#include "TestResult.h"
#include "Failure.h"


Test::Test (const std::string& testName) : name (testName)
{
	TestRegistry::addTest (this);
}


void Test::run (TestResult& result)
{
#ifndef DONT_CATCH_EXCEPTIONS
    try
    {
#endif
        setup();
	    runTest (result);
#ifndef DONT_CATCH_EXCEPTIONS
    }
    catch (Exception &e) {
//        SetColor(LightRed,Black);
        result.addFailure (Failure (String("Unhandled exception ["+e.Message+"]").c_str(), name, "", 0)); \
//        SetColor(LightGray,Black);
    }
#endif
    teardown();
	result.testWasRun();
}

