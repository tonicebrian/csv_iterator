#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/XmlOutputter.h>
#include <cppunit/TextOutputter.h>
#include <fstream>

#include <cstdlib>

int main(int argc, char* argv[]) {
    // Define test variables
    using namespace CppUnit;
    using namespace std;

    TestResult controller;
    TestResultCollector result;
    controller.addListener(&result);

    TextUi::TestRunner runner;
    TestFactoryRegistry& registry = TestFactoryRegistry::getRegistry();
    Test* testToRun = registry.makeTest(); 

    runner.addTest(testToRun);
    runner.run(controller);
    
    // Write results into XML
    // ofstream xmlFileOut("cpptestresults.xml");
    // XmlOutputter xmlOut(&result, xmlFileOut);
    // xmlOut.write();
    // xmlFileOut.close();

    // And to the console
    TextOutputter textOutput(&result, std::cout);
    textOutput.write();
    
    return 0;
}

