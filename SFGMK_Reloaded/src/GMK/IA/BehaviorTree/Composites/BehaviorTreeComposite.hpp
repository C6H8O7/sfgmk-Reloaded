/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		22/03/2016
	@brief

--------------------------------------------------------------------------------------------------*/

#ifndef BEHAVIOR_TREE_COMPOSITE_HPP
#define BEHAVIOR_TREE_COMPOSITE_HPP

#include "stdafx.h"


namespace gmk
{
	class BehaviorTreeComposite : public Behavior
	{
		public:
			BehaviorTreeComposite();
			virtual ~BehaviorTreeComposite();

			r_void reInitChilds();

			virtual r_void addChild(Behavior* _Node);

		protected:
			vector<Behavior*> m_Childs;
	};
}


#endif