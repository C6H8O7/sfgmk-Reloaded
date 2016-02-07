/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		06/02/2016
	@brief

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMKR_COMPONENT_STEERING_OBSTACLE_AVOIDANCE_HPP
#define SFGMKR_COMPONENT_STEERING_OBSTACLE_AVOIDANCE_HPP

#include "stdafx.h"


class ComponentSteeringObstacleAvoidance : public ComponentSteering<gmk::SteeringObstacleAvoidance>
{
	public:
		ComponentSteeringObstacleAvoidance(GameObject* _parent);
		~ComponentSteeringObstacleAvoidance();

		virtual r_void OnUpdate(SFMLCanvas * _canvas);
		virtual r_void OnDraw(SFMLCanvas* _canvas);

		virtual r_void OnMembersUpdate();

	#ifdef SFGMKR_EDITOR
		virtual r_void OnRegistration();
	#endif

		virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
		virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

	private:
	#ifdef SFGMKR_EDITOR
		sf::VertexArray m_AheadVector;
	#endif
};


#endif