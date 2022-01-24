#include "utilities.hpp"

bool fileexists(std::string filename)
{
	int f = open(filename.c_str(), O_RDONLY);
	if (f == -1)
	{
		return false;
	}
	close(f);
	return true;
}