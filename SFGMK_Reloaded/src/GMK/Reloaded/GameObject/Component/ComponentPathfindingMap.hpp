#ifndef SFGMKR_COMPONENTPATHFINDINGMAP_HPP
#define SFGMKR_COMPONENTPATHFINDINGMAP_HPP

class ComponentPathfindingMap : public GameObjectComponent
{
	friend class GameObject;

public:

	ComponentPathfindingMap(GameObject* _parent);
	~ComponentPathfindingMap();

	virtual r_void OnUpdate(SFMLCanvas * _canvas);
	virtual r_void OnDraw(SFMLCanvas* _canvas);

	virtual r_void OnMembersUpdate();

#ifdef SFGMKR_EDITOR
	virtual r_void OnRegistration();
#endif

	virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
	virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

	gmk::PathfindingMap* getMapPtr();

private:

	gmk::PathfindingMap m_Map;

	r_string m_Path;
	r_bool m_PathChanged;
};

#endif