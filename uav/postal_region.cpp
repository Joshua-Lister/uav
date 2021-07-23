#include <string>
using namespace std;
struct address_metadata
{
	string post_code;
	int x_coord = 0, y_coord = 0;
	string out_code;
	string in_code;
	int id = -1;
};