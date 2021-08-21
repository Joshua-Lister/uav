#pragma once
#include <windows.h>
#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <iostream>
#include "clustering.h"
#include "Circuit.h"
#include "genetic_algorithm.h"
#include <chrono>
#include "driver_code.h"
#include "test.h"
//using namespace std;

int testnum = 0;
double testval = 0.0;

int run_main()
{
	//run_truck_tandem_drone("rural");
	//TestClass test_software("Drone Delivery Software");
	//test_software.run_tests();
	//run_tests();
	//try_str();
	result R = try_result();
	return 0;
}

int __cdecl DescribeException(PEXCEPTION_POINTERS pData)
{
	// Clear the exception or else every FP instruction will
	// trigger it again.
	_clearfp();

	DWORD exceptionCode = pData->ExceptionRecord->ExceptionCode;
	const char* pDescription = nullptr;
	switch (exceptionCode)
	{
	case STATUS_FLOAT_INVALID_OPERATION:
		pDescription = "float invalid operation";
		break;
	case STATUS_FLOAT_DIVIDE_BY_ZERO:
		pDescription = "float divide by zero";
		break;
	case STATUS_FLOAT_OVERFLOW:
		pDescription = "float overflow";
		break;
	case STATUS_FLOAT_UNDERFLOW:
		pDescription = "float underflow";
		break;
	case STATUS_FLOAT_INEXACT_RESULT:
		pDescription = "float inexact result";
		break;
	case STATUS_FLOAT_MULTIPLE_TRAPS:
		// This seems to occur with SSE code.
		pDescription = "float multiple traps";
		break;
	default:
		pDescription = "unknown exception";
		break;
	}

	void* pErrorOffset = 0;
#if defined(_M_IX86)
	void* pIP = (void*)pData->ContextRecord->Eip;
	pErrorOffset = (void*)pData->ContextRecord->FloatSave.ErrorOffset;
#elif defined(_M_X64)
	void* pIP = (void*)pData->ContextRecord->Rip;
#else
#error Unknown processor
#endif

	cout << "Crash with exception " << exceptionCode << "(" << pDescription << ") at " << pIP << "! (" << testnum << ")" << endl;

	if (pErrorOffset)
	{
		// Float exceptions may be reported in a delayed manner — report the
		// actual instruction as well.
		cout << "Faulting instruction may actually be at " << pErrorOffset << endl;
	}

	return EXCEPTION_EXECUTE_HANDLER;
}

int main()
{
	_fpreset();
	unsigned original_mask;
	_controlfp_s(&original_mask, 0, 0);
	unsigned mask = original_mask;
	mask &= ~_EM_ZERODIVIDE;
	mask &= ~_EM_OVERFLOW;
	mask &= ~_EM_INVALID;
	_clearfp();
	_controlfp_s(&original_mask, mask, _MCW_EM);

	_try
	{
		return run_main();
	}

	_except(DescribeException(GetExceptionInformation()))
	{
		cout << " with testnum = " << testnum << " and testval= " << testval << endl;
	}
	

	_controlfp_s(0, original_mask, _MCW_EM);
}