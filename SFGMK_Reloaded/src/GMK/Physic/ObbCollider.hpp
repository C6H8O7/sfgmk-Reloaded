/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		15/06/2015
	@brief

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMK_OBB_COLLIDER_HPP
#define SFGMK_OBB_COLLIDER_HPP

namespace gmk
{
	class ObbCollider : public Collider
	{
		protected:

			sf::Vector2f m_Size;
			sf::Vector2f m_Offset;

		public:

			ObbCollider(GameObject* _gameobject);
			~ObbCollider();
	};
}

#endif