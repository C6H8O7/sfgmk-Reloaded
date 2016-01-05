#ifndef SFGMKR_COMPONENTCOLLIDER_HPP
#define SFGMKR_COMPONENTCOLLIDER_HPP

class ComponentCollider : public GameObjectComponent
{
	friend class GameObject;

public:

	ComponentCollider(GameObject* _parent);
	~ComponentCollider();

	virtual r_void OnUpdate(SFMLCanvas * _canvas);
	virtual r_void OnDraw(SFMLCanvas* _canvas);

	virtual r_void OnMembersUpdate();

#ifdef SFGMKR_EDITOR
	virtual r_void OnRegistration();
#endif

	virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
	virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

	r_void setType(gmk::eCOLLIDER_TYPE _type);
	r_void initType(gmk::eCOLLIDER_TYPE _type);

private:

	gmk::Collider m_Collider;

	bool m_TypeChanged;
	gmk::eCOLLIDER_TYPE m_Type;

	bool m_SizeChanged;
	float m_SizeX, m_SizeY;
};

#endif