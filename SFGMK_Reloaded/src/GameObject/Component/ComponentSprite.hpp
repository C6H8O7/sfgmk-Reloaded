#ifndef SFGMKR_COMPONENTSPRITE_HPP
#define SFGMKR_COMPONENTSPRITE_HPP

class ComponentSprite : public GameObjectComponent
{
	friend class GameObject;

public:

	ComponentSprite(GameObject* _parent);
	~ComponentSprite();

	virtual void OnUpdate(SFMLCanvas * _canvas);
	virtual void OnDraw(SFMLCanvas* _canvas);

	virtual void OnMembersUpdate();

#ifdef SFGMKR_EDITOR
	virtual void OnRegistration();
#endif

	virtual void OnXMLSave(tinyxml2::XMLElement* _element);
	virtual void OnXMLLoad(tinyxml2::XMLElement* _element);

private:

	sf::Texture m_Texture;
	sf::Sprite m_Sprite;

	float m_OriginX;
	float m_OriginY;
	bool m_OriginChanged;

	sf::Color m_Color;
	bool m_ColorChanged;

	std::string m_Path;
	bool m_PathChanged;
};

#endif