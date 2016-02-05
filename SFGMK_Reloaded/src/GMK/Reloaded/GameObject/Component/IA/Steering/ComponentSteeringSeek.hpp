#ifndef SFGMKR_COMPONENTSTEERINGSEEK_HPP
#define SFGMKR_COMPONENTSTEERINGSEEK_HPP

#include "stdafx.h"


class ComponentSteeringSeek : public ComponentSteering<gmk::SteeringSeek>
{
	public:
		ComponentSteeringSeek(GameObject* _parent);
		~ComponentSteeringSeek();

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