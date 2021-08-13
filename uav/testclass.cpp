#include "testclass.h"

// Constructor
TestClass::TestClass(std::string title)
    : title(title) {}

// Destructor
TestClass::~TestClass()
{
    // Generate summary of tests outcome at end of scope
    this->createSummary();
}

void TestClass::test(bool (*test_func)(), std::string title)
{
    int total = this->testsFailed + this->testsSucceeded;

    // Print title
    std::cout << std::endl
        << BLUE << "Test " << total + 1 << ": " << title << RESET_COLOR << std::endl;

    bool outcome = test_func();

    if (outcome)
    {
        this->testsSucceeded += 1;
        std::cout << GREEN << "Passed" << RESET_COLOR << std::endl;
    }
    else
    {
        this->testsFailed += 1;
        std::cout << RED << "Failed" << RESET_COLOR << std::endl;
    }
}

void TestClass::Error(std::string message)
{
    std::cerr << RED << message << RESET_COLOR << std::endl;
}

void TestClass::createSummary()
{
    int total = this->testsFailed + this->testsSucceeded;
    std::cout << std::endl;
    if (this->testsFailed == 0)
    {
        std::cout << GREEN << this->title << ": " << total << "/" << total << " tests passed." << RESET_COLOR << std::endl;
    }
    else
    {
        std::cout << RED << this->title << ": "
            << " " << this->testsFailed << "/" << total << " tests failed." << RESET_COLOR << std::endl
            << std::endl;
    }
}