/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		02/02/2016
	@brief		

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMKR_COMPONENT_STEERING_FLEE_HPP
#define SFGMKR_COMPONENT_STEERING_FLEE_HPP

#include "stdafx.h"


class ComponentSteeringFlee : public ComponentSteering
{
	public:
		ComponentSteeringFlee(GameObject* _parent);
		~ComponentSteeringFlee();

		virtual r_void OnUpdate(SFMLCanvas * _canvas);
		virtual r_void OnDraw(SFMLCanvas* _canvas);

		virtual r_void OnMembersUpdate();

	#ifdef SFGMKR_EDITOR
		virtual r_void OnRegistration();
	#endif

		virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
		virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);
};

#endif