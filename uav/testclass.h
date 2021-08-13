#pragma once
#include <iostream>
#include <string>

// Colours for text output
#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET_COLOR "\033[0m"
#define BLUE "\033[34m"

class TestClass {
public:
	TestClass(std::string title);
	~TestClass();
	void test(bool(*test_func)(), std::string title);
	static void Error(std::string message);
	void createSummary();

private:
	int testsFailed = 0;
	int testsSucceeded = 0;
	std::string title;

	void createSummary();
};