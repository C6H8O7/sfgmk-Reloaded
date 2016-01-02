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
		public:

			ObbCollider(GameObject* _gameobject);
			~ObbCollider();
	};
}

#endif