/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		05/02/2016
	@brief

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMKR_COMPONENT_STEERING_FORMATION_HPP
#define SFGMKR_COMPONENT_STEERING_FORMATION_HPP

#include "stdafx.h"

class ComponentSteeringFormation : public GameObjectComponent
{
public:

	ComponentSteeringFormation(GameObject* _parent);
	~ComponentSteeringFormation();

	virtual r_void OnUpdate(SFMLCanvas * _canvas);
	virtual r_void OnDraw(SFMLCanvas* _canvas);

	virtual r_void OnMembersUpdate();

#ifdef SFGMKR_EDITOR
	virtual r_void OnRegistration();
#endif

	virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
	virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

private:

	gmk::SteeringFormation m_Formation;

	r_string m_FormationName;
	r_bool m_FormationNameChanged = false;

	r_string m_LeaderName;
	r_bool m_LeaderNameChanged = false;
};


#endif