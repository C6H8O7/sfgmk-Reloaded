/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		22/03/2016
	@brief

--------------------------------------------------------------------------------------------------*/

#ifndef BEHAVIOR_TREE_REPEATER_HPP
#define BEHAVIOR_TREE_REPEATER_HPP

#include "stdafx.h"


namespace gmk
{
	class BehaviorTreeRepeater : public BehaviorTreeDecorator
	{
		public:
			BehaviorTreeRepeater(const r_bool& _IsInfinite, const r_uint32& _RepeatNumber = 2U);
			virtual ~BehaviorTreeRepeater();

			virtual r_void reInit();

			virtual const eBEHAVIOR_STATUS& initialise(const r_float& _DeltaTime);
			virtual const eBEHAVIOR_STATUS& update(const r_float& _DeltaTime);
			virtual const eBEHAVIOR_STATUS& terminate(const r_float& _DeltaTime);

		protected:
			r_bool m_bIsInfinite;
			r_uint32 m_uiRepeatNumber;
			r_uint32 m_uiActualRepeat;
	};
}


#endif