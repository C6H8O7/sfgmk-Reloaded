/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		08/02/2016
	@brief

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMKR_COMPONENT_STEERING_WANDER_HPP
#define SFGMKR_COMPONENT_STEERING_WANDER_HPP

#include "stdafx.h"


class ComponentSteeringWander : public ComponentSteering
{
	public:
		ComponentSteeringWander(GameObject* _parent);
		~ComponentSteeringWander();

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
		sf::CircleShape m_Circle;
	#endif

		r_float m_fCircleDistance;
		r_bool m_bCircleDistanceChanged;
		r_float m_fCircleRadius;
		r_bool m_bCircleRadiusChanged;
};


#endif