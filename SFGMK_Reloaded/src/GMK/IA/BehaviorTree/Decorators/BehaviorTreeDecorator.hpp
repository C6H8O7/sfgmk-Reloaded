/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		20/03/2016
	@brief

--------------------------------------------------------------------------------------------------*/

#ifndef BEHAVIOR_TREE_DECORATOR_HPP
#define BEHAVIOR_TREE_DECORATOR_HPP

#include "stdafx.h"


namespace gmk
{
	class BehaviorTreeDecorator : public Behavior
	{
		public:
			BehaviorTreeDecorator();
			virtual ~BehaviorTreeDecorator();

			virtual r_void reInit();
			r_void reInitChild();

			r_void addChild(Behavior* _Node);

		protected:
			Behavior* m_Child;
			eBEHAVIOR_STATUS m_ChildStatus;
	};
}


#endif