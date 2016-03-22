/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		22/03/2016
	@brief

--------------------------------------------------------------------------------------------------*/

#ifndef BEHAVIOR_TREE_SEQUENCE_HPP
#define BEHAVIOR_TREE_SEQUENCE_HPP

#include "stdafx.h"


namespace gmk
{
	class BehaviorTreeSequence : public BehaviorTreeComposite
	{
		public:
			BehaviorTreeSequence();
			virtual ~BehaviorTreeSequence();

			virtual r_void reInit();

			virtual const eBEHAVIOR_STATUS& initialise(const r_float& _DeltaTime);
			virtual const eBEHAVIOR_STATUS& update(const r_float& _DeltaTime);
			virtual const eBEHAVIOR_STATUS& terminate(const r_float& _DeltaTime);

			r_void addChild(Behavior* _Node);

		protected:
			r_uint32 m_uiSequenceLength;
			r_uint32 m_uiSequenceCurrentPosition;
			r_float m_fTaskTime;
			eBEHAVIOR_STATUS m_CurrentPositionStatus;
	};
}


#endif