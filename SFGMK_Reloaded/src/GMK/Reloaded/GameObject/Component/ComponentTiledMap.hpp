#ifndef SFGMKR_COMPONENTTILEDMAP_HPP
#define SFGMKR_COMPONENTTILEDMAP_HPP

class ComponentTiledMap : public GameObjectComponent
{
	friend class GameObject;

public:

	ComponentTiledMap(GameObject* _parent);
	~ComponentTiledMap();

	virtual void OnUpdate(SFMLCanvas * _canvas);
	virtual void OnDraw(SFMLCanvas* _canvas);

	virtual void OnMembersUpdate();

#ifdef SFGMKR_EDITOR
	virtual void OnRegistration();
#endif

	virtual void OnXMLSave(tinyxml2::XMLElement* _element);
	virtual void OnXMLLoad(tinyxml2::XMLElement* _element);

private:

	gmk::TiledMap m_Map;

	std::string m_Path;
	bool m_PathChanged;
};

#endif