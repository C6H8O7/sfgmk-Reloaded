/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		17/02/2016
	@brief

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMKR_COMPONENT_STEERING_SWARMING_HPP
#define SFGMKR_COMPONENT_STEERING_SWARMING_HPP

#include "stdafx.h"


class ComponentSteeringSwarming : public ComponentSteering
{
	public:
		ComponentSteeringSwarming(GameObject* _parent);
		~ComponentSteeringSwarming();

		virtual r_void OnUpdate(SFMLCanvas * _canvas);
		virtual r_void OnDraw(SFMLCanvas* _canvas);

		virtual r_void OnMembersUpdate();

	#ifdef SFGMKR_EDITOR
		virtual r_void OnRegistration();
	#endif

		virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
		virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

	private:
		r_float m_fAreaRadius;
		r_bool m_bAreaRadiusChanged;
};


#endif