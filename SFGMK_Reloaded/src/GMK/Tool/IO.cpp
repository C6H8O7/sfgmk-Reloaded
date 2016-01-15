#include "stdafx.h"

namespace gmk
{
	r_int8* loadFile(r_string _path)
	{
		r_int8* content = 0;

		sf::FileInputStream fs;

		if (!fs.open(_path))
			return content;

		sf::Int64 size = fs.getSize();

		content = new r_int8[size + 1];

		fs.read((r_void*)content, size);

		content[size] = 0;

		return content;
	}

	r_string getFileContent(r_string _path)
	{
		r_int8* content = loadFile(_path);

		if (!content)
			return "ERROR";

		r_string contentString = content;

		delete content;
		return contentString;
	}

	std::vector<r_string> getFileLines(r_string _path)
	{
		return stringSplit(getFileContent(_path), '\n');
	}

	std::vector<r_string> stringSplit(r_string _string, r_int8 _tok)
	{
		std::vector<r_string> split;

		std::stringstream stream(_string);
		std::string item;

		while (std::getline(stream, item, _tok))
		{
			split.push_back(item);
		}

		return split;
	}
}