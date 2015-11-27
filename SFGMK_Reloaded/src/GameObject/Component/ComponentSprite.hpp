#ifndef SFGMKR_COMPONENTSPRITE_HPP
#define SFGMKR_COMPONENTSPRITE_HPP

class ComponentSprite : public GameObjectComponent
{
public:

	ComponentSprite(GameObject* _parent);
	~ComponentSprite();

	virtual void OnUpdate();
	virtual void OnDraw(sf::RenderWindow* _render);

	virtual void OnRegistration();

private:

	sf::Texture m_Texture;
	sf::Sprite m_Sprite;

	bool m_OriginChanged;

	float m_OriginX;
	float m_OriginY;

	sf::Color m_Color;
	std::string m_Path;
	bool m_PathChanged;
};

#endif