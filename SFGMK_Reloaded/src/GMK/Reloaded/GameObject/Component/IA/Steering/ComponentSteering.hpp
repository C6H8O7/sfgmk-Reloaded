/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		05/02/2016
	@brief		Classe mère des steering components

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMKR_COMPONENT_STEERING_HPP
#define SFGMKR_COMPONENT_STEERING_HPP

#include "stdafx.h"


class ComponentSteering : public GameObjectComponent
{
	public:

		ComponentSteering(const r_string& _typeName, GameObject* _parent);
		virtual ~ComponentSteering();

		virtual r_void OnUpdate(SFMLCanvas * _canvas);

		r_void add();
		r_void remove();

		virtual r_void OnMembersUpdate();

	#ifdef SFGMKR_EDITOR
		virtual r_void OnRegistration();
	#endif

		virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
		virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

	protected:

		gmk::SteeringBehavior* m_Steering;

		r_float m_fSteeringWeight;
		r_bool m_bSteeringWeightChanged;

		r_string m_sTargetName;
		r_bool m_bTargetNameChanged;
};


#endif