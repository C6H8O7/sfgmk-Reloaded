/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		06/02/2016
	@brief		Classe de stockage de forme, utilise des gmk::vector

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMKR_COMPONENT_SHAPE_CONTAINER_HPP
#define SFGMKR_COMPONENT_SHAPE_CONTAINER_HPP

#include "stdafx.h"


class ComponentShapeContainer : public GameObjectComponent
{
	public:
		enum eCOMPONENT_SHAPE_TYPE
		{
			eCircle = 0,
		};

		ComponentShapeContainer(GameObject* _parent);
		~ComponentShapeContainer();

		virtual r_void OnUpdate(SFMLCanvas * _canvas);
		virtual r_void OnDraw(SFMLCanvas* _canvas);

		virtual r_void OnMembersUpdate();

	#ifdef SFGMKR_EDITOR
		virtual r_void OnRegistration();

		r_void AddFormToContainer(wxEvent& _event);
	#endif

		virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
		virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

		gmk::vector<sf::CircleShape*>* GetCircles();

	private:
		gmk::vector<sf::CircleShape*> m_Circles;
		gmk::vector<r_string*> m_CirclesNames;

		eCOMPONENT_SHAPE_TYPE m_Type;
		sf::Color m_Color;
		r_vector2f m_Position;
		r_float m_fRadius;
};


#endif