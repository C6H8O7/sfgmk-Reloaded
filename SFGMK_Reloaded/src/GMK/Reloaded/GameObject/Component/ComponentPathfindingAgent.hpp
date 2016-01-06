#ifndef SFGMKR_COMPONENTPATHFINDINGAGENT_HPP
#define SFGMKR_COMPONENTPATHFINDINGAGENT_HPP

class ComponentPathfindingAgent : public GameObjectComponent
{
	friend class GameObject;

public:

	ComponentPathfindingAgent(GameObject* _parent);
	~ComponentPathfindingAgent();

	virtual r_void OnUpdate(SFMLCanvas * _canvas);
	virtual r_void OnDraw(SFMLCanvas* _canvas);

	virtual r_void OnMembersUpdate();

#ifdef SFGMKR_EDITOR
	virtual r_void OnRegistration();
#endif

	virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
	virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

private:

	r_bool m_MapNameChanged;
	r_string m_MapName;

	r_float m_Speed;

	r_bool m_AlgoChanged;
	r_int32 m_Algo;

	gmk::PathfindingAgent m_Agent;

	gmk::PathfindingMap* m_Map;
	GameObject* m_MapObject;
};

#endif