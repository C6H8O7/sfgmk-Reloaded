#ifndef SFGMKR_COMPONENTCAMERA_HPP
#define SFGMKR_COMPONENTCAMERA_HPP

class ComponentCamera : public GameObjectComponent
{
	friend class GameObject;

public:

	ComponentCamera(GameObject* _parent);
	~ComponentCamera();

	virtual void OnUpdate(SFMLCanvas * _canvas);
	virtual void OnDraw(SFMLCanvas* _canvas);

#ifdef SFGMKR_EDITOR
	virtual void OnRegistration();
#endif

	virtual void OnXMLSave(tinyxml2::XMLElement* _element);
	virtual void OnXMLLoad(tinyxml2::XMLElement* _element);

private:

	float m_Width, m_Height;
	bool m_SizeChanged;

	float m_Zoom;
	bool m_ZoomChanged;

	float m_SpriteWidth, m_SpriteHeight;
	bool m_SpriteInit;
	sf::Texture m_Texture;
	sf::Sprite m_Sprite;

	sf::View m_View;
};

#endif