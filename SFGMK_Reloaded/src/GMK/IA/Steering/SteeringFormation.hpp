#ifndef SFGMKR_STEERINGFORMATION_HPP
#define SFGMKR_STEERINGFORMATION_HPP

#include "stdafx.h"

namespace gmk
{
	class SteeringFormation
	{
	public:

		SteeringFormation();
		virtual ~SteeringFormation();

		virtual r_void update();
		virtual r_vector2f getPosition(GameObject* _unit);

		r_void setLeader(GameObject* _leader);
		r_void setLeader(r_string _leader);
		GameObject* getLeader();

		r_void setName(r_string _name);
		r_string getName();

	protected:

		GameObject* m_Leader = 0;
		r_string m_LeaderName = "";
	
		r_string m_Name = "";

		r_uint32 m_CurrentPositionIndex = 0;
		r_uint32 m_LastFrameMaxIndex = 0;
	};
}

#endif