/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		05/02/2016
	@brief

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMKR_COMPONENT_STEERING_ARRIVAL_HPP
#define SFGMKR_COMPONENT_STEERING_ARRIVAL_HPP

#include "stdafx.h"


class ComponentSteeringArrival : public ComponentSteering
{
	public:
		ComponentSteeringArrival(GameObject* _parent);
		~ComponentSteeringArrival();

		virtual r_void OnDraw(SFMLCanvas* _canvas);

		virtual r_void OnMembersUpdate();

	#ifdef SFGMKR_EDITOR
		virtual r_void OnRegistration();
	#endif

		virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
		virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

	private:
		r_float m_fSlowingDistance;
		r_bool m_bSlowingDistanceChanged;
};


#endif