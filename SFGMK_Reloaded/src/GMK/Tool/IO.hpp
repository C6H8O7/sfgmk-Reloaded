#include "stdafx.h"

#ifndef SFGMKR_IO_HPP
#define SFGMKR_IO_HPP

namespace gmk
{
	r_int8* loadFile(r_string _path);
	r_string getFileContent(r_string _path);
	std::vector<r_string> getFileLines(r_string _path);
	std::vector<r_string> stringSplit(r_string _string, r_int8 _tok);
}

#endif