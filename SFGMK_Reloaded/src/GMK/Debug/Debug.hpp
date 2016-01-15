#ifndef SFGMKR_DEBUG_HPP
#define SFGMKR_DEBUG_HPP

#include "stdafx.h"

namespace gmk
{
	class Debug
	{
	public:

		Debug();

		bool selected;
		bool collisionEnabled;

		static r_void Log(r_string _log);
	};
}

#endif