#include "stdafx.h"

ComponentSelector::ComponentSelector(GameObject* _parent)
	: GameObjectComponent("Selector", _parent), m_Selector(_parent)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif
}

ComponentSelector::~ComponentSelector()
{

}

r_void ComponentSelector::OnUpdate(SFMLCanvas * _canvas)
{
#ifdef SFGMKR_EDITOR
	if (_canvas->isEditor())
		return;
#endif

	if (!_canvas->isPlaying)
		return;

	m_Selector.update(_canvas);

	gmk::Selector::eSELECTOR_STATE state = m_Selector.getState();

	if (state == gmk::Selector::eSELECTOR_STATE::SELECTION)
		parent->debug.collisionEnabled = true;
	else
		parent->debug.collisionEnabled = false;
}

r_void ComponentSelector::OnDraw(SFMLCanvas* _canvas)
{

}

r_void ComponentSelector::OnMembersUpdate()
{

}

#ifdef SFGMKR_EDITOR
r_void ComponentSelector::OnRegistration()
{
	beginRegister();

	endRegister();
}
#endif

r_void ComponentSelector::OnXMLSave(tinyxml2::XMLElement* _element)
{

}

r_void ComponentSelector::OnXMLLoad(tinyxml2::XMLElement* _element)
{

}