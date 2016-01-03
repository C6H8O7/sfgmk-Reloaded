/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		15/06/2015
	@brief		Objet physique utilis� pour d�tecter les collisions

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMK_COLLIDER_HPP
#define SFGMK_COLLIDER_HPP

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

		public:

			Collider(GameObject* _gameobject);
			~Collider();

			const eCOLLIDER_TYPE& getType();

			const r_bool& isActive();
			r_void setActive(r_bool _Boolean);

			const r_bool& Collide();
			r_void setCollide(r_bool _Boolean);

			const r_vector2f& getSize();
			r_void setSize(r_vector2f _size);

			const r_vector2f getOffset();
			r_void setOffset(r_vector2f _offset);
	};
}

#endif