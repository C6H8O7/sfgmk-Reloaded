/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		02/02/2016
	@brief		

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMKR_COMPONENT_STEERING_FLEE_HPP
#define SFGMKR_COMPONENT_STEERING_FLEE_HPP

#include "stdafx.h"


class ComponentSteeringFlee : public GameObjectComponent
{
	friend class GameObject;

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

	private:
		gmk::SteeringFlee m_Flee;

		r_string m_TargetName;
		r_bool m_TargetNameChanged;

		r_float m_fWeight;
		r_bool m_bWeightChanged;
};

#endif