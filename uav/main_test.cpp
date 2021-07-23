#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <iostream>
#include "clustering.h"
//using namespace std;

int main()
{
	read_data tets("postal_data.txt");
	tets.fill_data();
	//tets.print_data("Post_codes");
	//cout << tets.data[0].y_coord<<  "\n";
	//cout << "hi\n";
	clustering cl(1, 2, tets);
	cl.run_K_means();
	return 0;
}