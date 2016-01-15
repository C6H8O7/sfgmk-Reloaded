#include "stdafx.h"

namespace gmk
{
	Debug::Debug() : selected(false), collisionEnabled(true)
	{

	}

	r_void Debug::Log(r_string _log)
	{
#ifdef SFGMKR_ANDROID
		FILE* f = fopen("/sdcard/sfgmkr.txt", "a+");
		fputs((_log + "\n").c_str(), f);
		fflush(f);
		fclose(f);
#else
		std::cout << _log << std::endl;
#endif
	}
}