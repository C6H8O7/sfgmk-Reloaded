/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		18/02/2016
	@brief

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMKR_COMPONENT_STEERING_ALIGNMENT_HPP
#define SFGMKR_COMPONENT_STEERING_ALIGNMENT_HPP

#include "stdafx.h"


class ComponentSteeringAlignment : public ComponentSteering
{
	public:
		ComponentSteeringAlignment(GameObject* _parent);
		~ComponentSteeringAlignment();

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