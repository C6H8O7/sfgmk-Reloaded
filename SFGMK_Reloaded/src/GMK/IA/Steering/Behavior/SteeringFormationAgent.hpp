/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		05/02/2016
	@brief		

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMKR_STEERING_FORMATIONAGENT_HPP
#define SFGMKR_STEERING_FORMATIONAGENT_HPP

#include "stdafx.h"

namespace gmk
{
	class SteeringFormationAgent : public SteeringBehavior
	{
	public:

		SteeringFormationAgent(GameObject* _gameobject);

		r_vector2f update(r_float _deltaTime) override;

		r_void setSteeringFormation(r_string _name);
		r_string getSteeringFormation();

	protected:

		r_string m_FormationName;
	};
}


#endif