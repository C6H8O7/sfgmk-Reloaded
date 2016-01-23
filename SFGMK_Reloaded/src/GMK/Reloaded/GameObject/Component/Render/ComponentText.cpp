#include "stdafx.h"

ComponentText::ComponentText(GameObject* _parent)
	: GameObjectComponent("Text", _parent)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	parent->text = "NULL";
	m_Size = 20;
	m_Color = sf::Color::White;
}

ComponentText::~ComponentText()
{

}

r_void ComponentText::OnUpdate(SFMLCanvas * _canvas)
{
	m_TextRenderer.setString(parent->text);
	m_TextRenderer.setCharacterSize(m_Size);
	m_TextRenderer.setFillColor(m_Color);

	m_TextRenderer.setPosition(parent->transform.position);
	m_TextRenderer.setScale(parent->transform.scale);
	m_TextRenderer.setRotation(parent->transform.rotation);
}

r_void ComponentText::OnDraw(SFMLCanvas* _canvas)
{
	_canvas->draw(m_TextRenderer);
}

r_void ComponentText::OnMembersUpdate()
{
	if (m_FontPathChanged)
	{
		m_FontPathChanged = false;

		if (m_FontPath.size())
		{
			m_Font.loadFromFile(gmk::AssetsManager::GetSingleton()->getAssetPath(m_FontPath));
			m_TextRenderer.setFont(m_Font);
		}
	}
}

#ifdef SFGMKR_EDITOR
r_void ComponentText::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Font", &m_FontPath, &m_FontPathChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Text", &parent->text);
	registerProperty(ePROPERTY_TYPE::TYPE_INT, "Size", &m_Size);
	registerProperty(ePROPERTY_TYPE::TYPE_COLOR, "Color", &m_Color);

	endRegister();
}
#endif

r_void ComponentText::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("font", m_FontPath.c_str());
	_element->SetAttribute("text", parent->text.c_str());
	_element->SetAttribute("size", m_Size);

	_element->SetAttribute("r", m_Color.r);
	_element->SetAttribute("g", m_Color.g);
	_element->SetAttribute("b", m_Color.b);
	_element->SetAttribute("a", m_Color.a);
}

r_void ComponentText::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	m_FontPath = _element->Attribute("font");
	m_FontPathChanged = true;

	parent->text = _element->Attribute("text");

	m_Size = _element->IntAttribute("size");

	m_Color = sf::Color(_element->IntAttribute("r"), _element->IntAttribute("g"), _element->IntAttribute("b"), _element->IntAttribute("a"));
}