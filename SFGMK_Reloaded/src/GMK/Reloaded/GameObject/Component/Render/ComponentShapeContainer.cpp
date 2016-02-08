#include "stdafx.h"

ComponentShapeContainer::ComponentShapeContainer(GameObject* _parent)
	: GameObjectComponent("ShapeContainer", _parent), m_Type(eCircle), m_fRadius(0.0f)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif
}

ComponentShapeContainer::~ComponentShapeContainer()
{
	m_Circles.deleteAndClear();
	m_CirclesNames.deleteAndClear();
}

r_void ComponentShapeContainer::OnUpdate(SFMLCanvas * _canvas)
{

}

r_void ComponentShapeContainer::OnDraw(SFMLCanvas* _canvas)
{
#ifdef SFGMKR_EDITOR
	if( _canvas->isEditor() )
	{
		for( unsigned int i(0U); i < m_Circles.size(); i++ )
			_canvas->draw(*m_Circles[i]);
	}
#endif
}

r_void ComponentShapeContainer::OnMembersUpdate()
{

}

#ifdef SFGMKR_EDITOR
r_void ComponentShapeContainer::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Pos X", &m_Position.x);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Pos Y", &m_Position.y);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Radius", &m_fRadius);
	registerProperty(ePROPERTY_TYPE::TYPE_COLOR, "Color", &m_Color);
	registerProperty(ePROPERTY_TYPE::TYPE_BUTTON, "Add Form", 0, 0, false, (wxObjectEventFunction)&ComponentShapeContainer::AddFormToContainer);

	registerProperty(ePROPERTY_TYPE::TYPE_INT, "Circles:", (void*)&m_Circles.size(), 0, true);
	m_CirclesNames.clear();

	for( unsigned int i(0U); i < m_Circles.size(); i++ )
	{
		m_CirclesNames.push_back(new r_string(std::to_string(i) + " Pos: " + std::to_string(m_Circles[i]->getPosition().x) + ' ' + std::to_string(m_Circles[i]->getPosition().y)
																 + " Rad: " + std::to_string(m_Circles[i]->getRadius())));

		registerProperty(ePROPERTY_TYPE::TYPE_STRING, "", m_CirclesNames[i], 0, true);
	}

	endRegister();
}

r_void ComponentShapeContainer::AddFormToContainer(wxEvent& _event)
{
	sf::CircleShape* NewCircle(NULL);

	switch( m_Type )
	{
		case eCircle:
			NewCircle = new sf::CircleShape(m_fRadius);
			NewCircle->setPosition(m_Position);
			NewCircle->setFillColor(m_Color);
			m_Circles.push_back(NewCircle);
			break;

		default:
			break;
	}

	OnPropertiesReload();
}
#endif


r_void ComponentShapeContainer::OnXMLSave(tinyxml2::XMLElement* _element)
{
	tinyxml2::XMLElement* ShapeElement = _element->GetDocument()->NewElement("Circles");
	ShapeElement->SetAttribute("number", m_Circles.size());

	for( r_uint32 i(0); i < m_Circles.size(); i++ )
	{
		tinyxml2::XMLElement* VariablesElement = ShapeElement->GetDocument()->NewElement("Variables");

		VariablesElement->SetAttribute("pos_X", m_Circles[i]->getPosition().x);
		VariablesElement->SetAttribute("pos_Y", m_Circles[i]->getPosition().y);
		VariablesElement->SetAttribute("radius", m_Circles[i]->getRadius());

		sf::Color Color = m_Circles[i]->getFillColor();
		VariablesElement->SetAttribute("R", (sf::Uint8)(*(sf::Color*)&Color).r);
		VariablesElement->SetAttribute("G", (sf::Uint8)(*(sf::Color*)&Color).g);
		VariablesElement->SetAttribute("B", (sf::Uint8)(*(sf::Color*)&Color).b);
		VariablesElement->SetAttribute("A", (sf::Uint8)(*(sf::Color*)&Color).a);

		ShapeElement->LinkEndChild(VariablesElement);
	}

	_element->LinkEndChild(ShapeElement);
}

r_void ComponentShapeContainer::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	tinyxml2::XMLElement* ShapeElement = _element->FirstChildElement("Circles");

	tinyxml2::XMLElement* VariablesElement = ShapeElement->FirstChildElement("Variables");

	while( VariablesElement )
	{
		sf::CircleShape* NewCircle = new sf::CircleShape(VariablesElement->FloatAttribute("radius"));
		NewCircle->setPosition(VariablesElement->FloatAttribute("pos_X"), VariablesElement->FloatAttribute("pos_Y"));
		NewCircle->setFillColor(sf::Color(VariablesElement->IntAttribute("R"), VariablesElement->IntAttribute("G"), VariablesElement->IntAttribute("B"), VariablesElement->IntAttribute("A")));
		m_Circles.push_back(NewCircle);

		VariablesElement = VariablesElement->NextSiblingElement("Variables");
	}

#ifdef SFGMKR_EDITOR
	OnPropertiesReload();
#endif
}

gmk::vector<sf::CircleShape*>* ComponentShapeContainer::GetCircles()
{
	return &m_Circles;
}