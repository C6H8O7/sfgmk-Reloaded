/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		20/03/2016
	@brief

--------------------------------------------------------------------------------------------------*/

#ifndef BEHAVIOR_LEAF_HPP
#define BEHAVIOR_LEAF_HPP

#include "stdafx.h"


namespace gmk
{
	class BehaviorTreeLeaf : public Behavior
	{
		public:
			BehaviorTreeLeaf();
			~BehaviorTreeLeaf();

			virtual const eBEHAVIOR_STATUS& initialise(const r_float& _DeltaTime);
			virtual const eBEHAVIOR_STATUS& update(const r_float& _DeltaTime);
			virtual const eBEHAVIOR_STATUS& terminate(const r_float& _DeltaTime);
	};
}


#endif