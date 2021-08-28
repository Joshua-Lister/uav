#include <windows.h>
#include <stdexcept>
#include "intersection.h"


int main()
{
	intersection iss;
#if defined (_WIN32)
	std::string s;
	std::cin >> s;
	iss.run_which_windows(s);
#else
	iss.run_which_linux();
#endif
	std::cout << "\n******************************************************************************************************************\n";
	std::cout << "Many thanks to my supervisor Professor Stephen Neethling for his help and guidance throughout this project.\n";
	std::cout << "******************************************************************************************************************\n";
	return 0;
}
