/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		17/02/2016
	@brief

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMKR_COMPONENT_STEERING_COHESION_HPP
#define SFGMKR_COMPONENT_STEERING_COHESION_HPP

#include "stdafx.h"


class ComponentSteeringCohesion : public ComponentSteering
{
	public:
		ComponentSteeringCohesion(GameObject* _parent);
		~ComponentSteeringCohesion();

		virtual r_void OnUpdate(SFMLCanvas * _canvas);
		virtual r_void OnDraw(SFMLCanvas* _canvas);

		virtual r_void OnMembersUpdate();

	#ifdef SFGMKR_EDITOR
		virtual r_void OnRegistration();
	#endif

		virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
		virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

	private:
		r_float m_fDetectionDistanceMax;
		r_bool m_bDetectionDistanceMaxChanged;
};


#endif