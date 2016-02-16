/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		05/02/2016
	@brief

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMKR_COMPONENT_STEERING_FORMATIONAGENT_HPP
#define SFGMKR_COMPONENT_STEERING_FORMATIONAGENT_HPP

#include "stdafx.h"

class ComponentSteeringFormationAgent : public ComponentSteering
{
public:

	ComponentSteeringFormationAgent(GameObject* _parent);
	~ComponentSteeringFormationAgent();

	virtual r_void OnUpdate(SFMLCanvas * _canvas);
	virtual r_void OnDraw(SFMLCanvas* _canvas);

	virtual r_void OnMembersUpdate();

#ifdef SFGMKR_EDITOR
	virtual r_void OnRegistration();
#endif

	virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
	virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

private:

	r_string m_FormationName;
	r_bool m_FormationNameChanged = false;
};


#endif