#ifndef SFGMKR_COMPONENTPOLYGON_HPP
#define SFGMKR_COMPONENTPOLYGON_HPP

class ComponentPolygon : public GameObjectComponent
{
	friend class GameObject;

	public:
		ComponentPolygon(GameObject* _parent);
		~ComponentPolygon();

		virtual r_void OnUpdate(SFMLCanvas * _canvas);
		virtual r_void OnDraw(SFMLCanvas* _canvas);

		virtual r_void OnMembersUpdate();

	#ifdef SFGMKR_EDITOR
		virtual r_void OnRegistration();
		virtual r_void OnEditorUpdate();
	#endif

		virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
		virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

		private:
			gmk::Polygon m_Polygon;
			r_uint32 m_TriangleNumber;
};

#endif