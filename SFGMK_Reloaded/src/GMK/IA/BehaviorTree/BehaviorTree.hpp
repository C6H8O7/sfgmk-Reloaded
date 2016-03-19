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
	#define BEHAVIOR_TREE_FUNCTIONS_NUMBER 3U

	enum eBEHAVIOR_STATUS
	{
		BH_NOT_INITIALISED = 0,
		BH_RUNNING,
		BH_TERMINATING,
		BH_SUCCESS,
		BH_FAILURE,
		BH_ABORTED
	};

	class Behavior
	{
		public:
			Behavior() : m_Parent(NULL), m_Status(BH_NOT_INITIALISED) {}
			virtual ~Behavior() {}

			const eBEHAVIOR_STATUS& process(const r_float& _DeltaTime)
			{
				m_Status < BEHAVIOR_TREE_FUNCTIONS_NUMBER ?
					m_Status = (this->*m_Functions[m_Status])(_DeltaTime)
					: m_Status;

				return m_Status;
			}

			virtual const eBEHAVIOR_STATUS& initialise(const r_float& _DeltaTime) = 0;
			virtual const eBEHAVIOR_STATUS& update(const r_float& _DeltaTime) = 0;
			virtual const eBEHAVIOR_STATUS& terminate(const r_float& _DeltaTime) = 0;

			const eBEHAVIOR_STATUS& getStatus() const { return m_Status; }

			r_void setParent(Behavior* _Parent) { m_Parent = _Parent; }

		protected:
			Behavior* m_Parent;
			eBEHAVIOR_STATUS m_Status;
			const eBEHAVIOR_STATUS& (Behavior::*m_Functions[BEHAVIOR_TREE_FUNCTIONS_NUMBER])(const r_float&) = { &Behavior::initialise, &Behavior::update, &Behavior::terminate };
	};

	struct stBEHAVIOR_STATUS
	{
		eBEHAVIOR_STATUS Status;
		Behavior* Behavior;
	};

	class BehaviorTree
	{
		public:
			BehaviorTree(Behavior* _Root) : m_Root(_Root) { m_CurrentBehavior.Status = BH_NOT_INITIALISED; m_CurrentBehavior.Behavior = m_Root; }
			~BehaviorTree() { delete m_Root; }

			r_void update(const r_float& _DeltaTime)
			{
				m_CurrentBehavior.Status = m_CurrentBehavior.Behavior->process(_DeltaTime);
			}

			r_void setCurrentBehavior(Behavior* _Node, const eBEHAVIOR_STATUS& _Status = BH_NOT_INITIALISED) { m_CurrentBehavior.Behavior = _Node; m_CurrentBehavior.Status = _Status; }

		private:
			Behavior* m_Root;
			stBEHAVIOR_STATUS m_CurrentBehavior;
	};

	class BehaviorTreeLeaf : public Behavior
	{
		public:
			BehaviorTreeLeaf() {}
			~BehaviorTreeLeaf() {}

			virtual const eBEHAVIOR_STATUS& initialise(const r_float& _DeltaTime) 
			{
				std::cout << "Leaf initialise" << std::endl;
				m_Status = BH_RUNNING;
				return m_Status;
			}
			virtual const eBEHAVIOR_STATUS& update(const r_float& _DeltaTime) 
			{
				std::cout << "Leaf Update" << std::endl;
				m_Status = BH_TERMINATING;
				return m_Status;
			}
			virtual const eBEHAVIOR_STATUS& terminate(const r_float& _DeltaTime) 
			{
				std::cout << "Leaf terminate" << std::endl;
				m_Status = BH_SUCCESS;
				return m_Status;
			}
	};

	class BehaviorTreeDecorator : public Behavior
	{
		public:
			BehaviorTreeDecorator() : m_ChildStatus(BH_NOT_INITIALISED) {}
			virtual ~BehaviorTreeDecorator() { SAFE_DELETE(m_Child); }

			r_void addChild(Behavior* _Node) { m_Child = _Node; m_Child->setParent(this); }

		protected:
			Behavior* m_Child;
			eBEHAVIOR_STATUS m_ChildStatus;
	};

	class BehaviorTreeRepeater : public BehaviorTreeDecorator
	{
		public:
			BehaviorTreeRepeater(const r_bool& _IsInfinite, const r_uint32& _RepeatNumber = 2U) : m_bIsInfinite(_IsInfinite), m_uiRepeatNumber(_RepeatNumber), m_uiActualRepeat(0U) {}
			virtual ~BehaviorTreeRepeater() {}

			virtual const eBEHAVIOR_STATUS& initialise(const r_float& _DeltaTime)
			{
				std::cout << "Repeater initialise" << std::endl;
				m_Status = BH_RUNNING;
				return m_Status;
			}
			virtual const eBEHAVIOR_STATUS& update(const r_float& _DeltaTime)
			{
				std::cout << "Repeater Update: " << m_uiActualRepeat << " iteration" << std::endl;
				
				m_ChildStatus = m_Child->process(_DeltaTime);
				if( m_ChildStatus > BH_TERMINATING )
					m_uiActualRepeat++;

				if( !m_bIsInfinite || !(m_uiActualRepeat < m_uiRepeatNumber) )
					m_Status = BH_TERMINATING;

				return m_Status;
			}
			virtual const eBEHAVIOR_STATUS& terminate(const r_float& _DeltaTime)
			{
				std::cout << "Repeater terminate" << std::endl;
				m_Status = BH_SUCCESS;
				return m_Status;
			}

		protected:
			r_bool m_bIsInfinite;
			r_uint32 m_uiRepeatNumber;
			r_uint32 m_uiActualRepeat;
	};

	class BehaviorTreeComposite : public Behavior
	{
		public:
			BehaviorTreeComposite() {}
			virtual ~BehaviorTreeComposite() { m_Childs.deleteAndClear(); }

			virtual r_void addChild(Behavior* _Node) { m_Childs.push_back(_Node); _Node->setParent(this); }

		protected:
			vector<Behavior*> m_Childs;
	};

	class BehaviorTreeSequence : public BehaviorTreeComposite
	{
		public:
			BehaviorTreeSequence() : m_uiSequenceLength(0U), m_uiSequenceCurrentPosition(0U), m_fTaskTime(0.0f), m_CurrentPositionStatus(BH_NOT_INITIALISED) {}
			virtual ~BehaviorTreeSequence() {}

			virtual const eBEHAVIOR_STATUS& initialise(const r_float& _DeltaTime)
			{
				std::cout << "Sequence initialise" << std::endl;
				m_Status = BH_RUNNING;
				return m_Status;
			}

			virtual const eBEHAVIOR_STATUS& update(const r_float& _DeltaTime) 
			{
				std::cout << "Sequence update" << std::endl;
				std::cout << m_fTaskTime << "    current task: " << m_uiSequenceCurrentPosition << std::endl;

				m_fTaskTime += _DeltaTime;
				m_CurrentPositionStatus = m_Childs[m_uiSequenceCurrentPosition]->process(_DeltaTime);

				if( m_CurrentPositionStatus > BH_TERMINATING )
				{
					m_fTaskTime = 0.0f;
					m_uiSequenceCurrentPosition++;
				}

				if( m_uiSequenceCurrentPosition < m_uiSequenceLength )
					return BH_RUNNING;
				else
					return BH_SUCCESS;
			}

			virtual const eBEHAVIOR_STATUS& terminate(const r_float& _DeltaTime)
			{
				std::cout << "Sequence terminate" << std::endl;
				return m_Status;
			}

			r_void addChild(Behavior* _Node) { m_Childs.push_back(_Node); _Node->setParent(this); m_uiSequenceLength++; }

		protected:
			r_uint32 m_uiSequenceLength;
			r_uint32 m_uiSequenceCurrentPosition;
			r_float m_fTaskTime;
			eBEHAVIOR_STATUS m_CurrentPositionStatus;
	};
}


#endif