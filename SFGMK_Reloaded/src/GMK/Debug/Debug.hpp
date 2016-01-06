#ifndef SFGMKR_DEBUG_HPP
#define SFGMKR_DEBUG_HPP

namespace gmk
{
	class Debug
	{
	public:

		Debug()
			: selected(false), collisionEnabled(true)
		{

		}

		bool selected;
		bool collisionEnabled;
	};
}

#endif