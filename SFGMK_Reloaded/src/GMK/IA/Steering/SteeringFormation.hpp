#ifndef SFGMKR_STEERINGFORMATION_HPP
#define SFGMKR_STEERINGFORMATION_HPP

#include "stdafx.h"

namespace gmk
{
	enum eSTEERING_FORMATION_FUNC
	{
		FORMATION_CIRCLE,
		FORMATION_V,
		FORMATION_LINE,
		FORMATION_COUNT
	};

	class SteeringFormation
	{
	public:

		typedef r_vector2f (gmk::SteeringFormation::*pSTEERING_FORMATION_FUNC)(GameObject* _unit);

		SteeringFormation();
		~SteeringFormation();

		r_void update();
		r_vector2f getPosition(GameObject* _unit);

		r_void setLeader(GameObject* _leader);
		GameObject* getLeader();

		GMK_CLASS_PROPERTY_FUNCS(r_string, m_LeaderName, LeaderName, r_void)
		GMK_CLASS_PROPERTY_FUNCS(r_string, m_Name, Name, r_void)
		GMK_CLASS_PROPERTY_FUNCS(eSTEERING_FORMATION_FUNC, m_FormationFunc, FormationFunc, r_void)

	protected:

		r_vector2f getPositionFormationCircle(GameObject* _unit);
		r_vector2f getPositionFormationV(GameObject* _unit);
		r_vector2f getPositionFormationLine(GameObject* _unit);

		GameObject* m_Leader = 0;
		r_string m_LeaderName = "";
	
		r_string m_Name = "";

		r_uint32 m_CurrentPositionIndex = 0;
		r_uint32 m_LastFrameMaxIndex = 0;

		eSTEERING_FORMATION_FUNC m_FormationFunc = FORMATION_CIRCLE;

		static pSTEERING_FORMATION_FUNC s_FormationFuncs[FORMATION_COUNT];
	};
}

#endif