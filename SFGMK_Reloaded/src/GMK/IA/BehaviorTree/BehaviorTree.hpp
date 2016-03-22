/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		16/03/2016
	@brief		

--------------------------------------------------------------------------------------------------*/

#ifndef BEHAVIOR_TREE_HPP
#define BEHAVIOR_TREE_HPP

#include "stdafx.h"


namespace gmk
{
	class BehaviorTree
	{
		public:
			BehaviorTree(Behavior* _Root = NULL);
			~BehaviorTree();

			r_void update(const r_float& _DeltaTime);

			r_void setRoot(Behavior* _Root);
			r_void setCurrentBehavior(Behavior* _Node, const eBEHAVIOR_STATUS& _Status = BH_NOT_INITIALISED);

		private:
			Behavior* m_Root;
			stBEHAVIOR_STATUS m_CurrentBehavior;
	};
}


#endif


/*gmk::BehaviorTreeLeaf Task1;
gmk::BehaviorTreeLeaf Task2;
gmk::BehaviorTreeLeaf Task3;

gmk::BehaviorTreeSequence MySequence;

gmk::BehaviorTreeRepeater MyRepeater(false, 2U);

gmk::BehaviorTree MyTree(&MyRepeater);

MySequence.addChild(&Task1);
MySequence.addChild(&Task2);
MySequence.addChild(&Task3);

MyRepeater.addChild(&MySequence);

MyTree.update(gmk::TimeManager::GetSingleton()->getDeltaTime());*/