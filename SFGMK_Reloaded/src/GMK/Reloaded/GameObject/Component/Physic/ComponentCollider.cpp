#include "stdafx.h"

ComponentCollider::ComponentCollider(GameObject* _parent)
	: GameObjectComponent("Collider", _parent), m_Collider(_parent)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	m_Type = m_Collider.getType();
}

ComponentCollider::~ComponentCollider()
{

}

r_void ComponentCollider::OnUpdate(SFMLCanvas * _canvas)
{
	if (parent->debug.collisionEnabled)
		m_Collider.setActive(true);
	else
		m_Collider.setActive(false);
}

r_void ComponentCollider::OnDraw(SFMLCanvas* _canvas)
{
#ifdef SFGMKR_EDITOR
	if (_canvas->isEditor())
		m_Collider.draw(_canvas);
#endif
}

r_void ComponentCollider::OnMembersUpdate()
{
	if (m_TypeChanged)
	{
		m_TypeChanged = false;
		m_Collider.setType(m_Type);
	}

	if (m_SizeChanged)
	{
		m_SizeChanged = false;
		m_Collider.setSize(r_vector2f(m_SizeX, m_SizeY));
	}

	if( m_bOffsetChanged )
	{
		m_bOffsetChanged = false;
		m_Collider.setOffset(m_Offset);
	}
}

#ifdef SFGMKR_EDITOR
r_void ComponentCollider::OnRegistration()
{
	beginRegister();

	GameObjectComponent::ComponentProperty* propertyType = registerProperty(ePROPERTY_TYPE::TYPE_ENUM, "Type", &m_Type, &m_TypeChanged);
	propertyType->wxChoices.Add("Sphere", gmk::eCOLLIDER_TYPE::eSphere);
	propertyType->wxChoices.Add("OBB", gmk::eCOLLIDER_TYPE::eOBB);

	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Size X", &m_SizeX, &m_SizeChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Size Y", &m_SizeY, &m_SizeChanged);

	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Offset X", &m_Offset.x, &m_bOffsetChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Offset Y", &m_Offset.y, &m_bOffsetChanged);

	endRegister();
}
#endif

r_void ComponentCollider::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("ctype", (r_int32)m_Type);
	_element->SetAttribute("x", m_SizeX);
	_element->SetAttribute("y", m_SizeY);
	_element->SetAttribute("offsetX", m_Offset.x);
	_element->SetAttribute("offsetY", m_Offset.y);
}

r_void ComponentCollider::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	m_Type = (gmk::eCOLLIDER_TYPE)_element->IntAttribute("ctype");
	m_TypeChanged = true;

	m_SizeX = _element->FloatAttribute("x");
	m_SizeY = _element->FloatAttribute("y");
	m_SizeChanged = true;

	m_Offset.x = _element->FloatAttribute("offsetX");
	m_Offset.y = _element->FloatAttribute("offsetY");
	m_bOffsetChanged = true;
}

r_void ComponentCollider::setType(gmk::eCOLLIDER_TYPE _type)
{
	m_Type = _type;
	m_Collider.setType(_type);
}

r_void ComponentCollider::initType(gmk::eCOLLIDER_TYPE _type)
{
	m_Type = _type;
	m_Collider.setType(_type);

	ComponentSprite* SpriteComponent = NULL;
	if( (SpriteComponent = (ComponentSprite*)parent->getComponent("Sprite")) )
	{
		sf::Vector2f SpriteSize = sf::Vector2f(SpriteComponent->getSprite()->getLocalBounds().width, SpriteComponent->getSprite()->getLocalBounds().height);

		if( m_Type == gmk::eCOLLIDER_TYPE::eSphere )
		{
			m_SizeX = MAX(SpriteSize.x, SpriteSize.y) * 0.5f;
			m_SizeY = 0.0f;
			m_Collider.setSize(r_vector2f(m_SizeX, m_SizeY));

			//Recentre le collider
			if( SpriteSize.x != SpriteSize.y )
			{
				if( SpriteSize.x < SpriteSize.y )
					m_Offset = r_vector2f(-(SpriteSize.y - SpriteSize.x) * 0.5f, 0.0f);
				else
					m_Offset = r_vector2f(0.0f, -(SpriteSize.x - SpriteSize.y) * 0.5f);
			}
		}
		else if( m_Type == gmk::eCOLLIDER_TYPE::eOBB )
		{
			m_SizeX = SpriteSize.x;
			m_SizeY = SpriteSize.y;
			m_Collider.setSize(r_vector2f(m_SizeX, m_SizeY));
		}
	}
	else
	{
		m_SizeX = 32.0f;
		m_SizeY = 32.0f;
		m_Collider.setSize(r_vector2f(m_SizeX, m_SizeY));
	}

	m_Collider.setOffset(m_Offset);
}

gmk::Collider* ComponentCollider::getCollider()
{
	return &m_Collider;
}