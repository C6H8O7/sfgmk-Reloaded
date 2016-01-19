/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		15/06/2015
	@brief		Objet physique utilisé pour détecter les collisions

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMK_COLLIDER_HPP
#define SFGMK_COLLIDER_HPP

#include "stdafx.h"

class GameObject;

namespace gmk
{
	enum eCOLLIDER_TYPE
	{
		eSphere = 1,
		eOBB = 2,
		eCOLLIDER_TYPE_NUMBER
	};

	class Collider
	{
		protected:

			eCOLLIDER_TYPE m_Type;

			r_bool m_bActive;
			r_bool m_bCollide;

			GameObject* m_GameObject;

			r_vector2f m_Size;
			r_vector2f m_Offset;

			std::vector<Collider*> m_CollidingWith;
			std::vector<Collider*> m_PrevCollidingWith;

		public:

			Collider(GameObject* _gameobject);
			~Collider();

			const eCOLLIDER_TYPE& getType();
			r_void setType(eCOLLIDER_TYPE _type);

			const r_bool& isActive();
			r_void setActive(r_bool _Boolean);

			const r_bool& isColliding();
			r_void setColliding(r_bool _Boolean);

			const r_vector2f& getSize();
			r_void setSize(r_vector2f _size);

			const r_vector2f getWorldSize();

			const r_vector2f getOffset();
			r_void setOffset(r_vector2f _offset);

			GameObject* getGameObject();
			r_void setGameObject(GameObject* _object);

			r_void draw(sf::RenderTarget* _render);

			r_void addCollidingWith(Collider* _collider);
			r_bool isCollidingWith(Collider* _collider);
			r_bool wasCollidingWith(Collider* _collider);
			r_bool beginCollidingWith(Collider* _collider);
			r_void updateCollidingWith();
	};
}

#endif