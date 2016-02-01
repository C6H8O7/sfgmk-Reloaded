#ifndef SFGMKR_COMPONENTPATHFINDINGMAP_HPP
#define SFGMKR_COMPONENTPATHFINDINGMAP_HPP

#include "stdafx.h"


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
		virtual r_void OnEditorUpdate();

		r_void LoadMapEvent(wxEvent& _event);
		r_void Generate(wxEvent& _event);
		r_void SaveMap(wxEvent& _event);
	#endif

		r_void LoadMap();

		virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
		virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

		gmk::PathfindingMap* getMapPtr();

	private:
		gmk::PathfindingMap m_Map;

		r_string m_Path;

		r_int32 m_CaseSize;
		r_bool m_CaseSizeChanged;

		r_vector2i m_MapSize;
		r_bool m_MapSizeChanged;

		r_int32 m_CaseNumber;
		r_int32 m_WallNumber;

		gmk::eMAP_GENERATION_TYPE m_GenerationType;
		r_uint32 m_MaxRoom;
		r_vector2i m_RoomMinSize, m_RoomMaxSize;
};


#endif