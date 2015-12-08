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
			sf::Vector2f m_Min;
			sf::Vector2f m_Max;

		public:

			ObbCollider(GameObject* _gameobject, sf::Vector2f _Size = sf::Vector2f(1.0f, 1.0f));
			~ObbCollider();
	};
}

#endif