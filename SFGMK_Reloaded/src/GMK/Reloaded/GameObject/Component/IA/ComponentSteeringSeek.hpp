#ifndef SFGMKR_COMPONENTSTEERINGSEEK_HPP
#define SFGMKR_COMPONENTSTEERINGSEEK_HPP

#include "stdafx.h"

class ComponentSteeringSeek : public GameObjectComponent
{
	friend class GameObject;

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

private:

	gmk::SteeringSeek m_Seek;

	r_string m_TargetName;
	r_bool m_TargetNameChanged;

	r_float m_fWeight;
	r_bool m_bWeightChanged;
};

#endif