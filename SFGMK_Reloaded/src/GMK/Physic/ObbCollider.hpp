/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		15/06/2015
	@brief

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMK_OBB_COLLIDER_HPP
#define SFGMK_OBB_COLLIDER_HPP

#include "stdafx.h"

namespace gmk
{
	class ObbCollider : public Collider
	{
		public:

			ObbCollider(GameObject* _gameobject);
			~ObbCollider();

			r_float getRadius();
			r_float getSquaredRadius();

			r_vector2f getMin();
			r_vector2f getMax();

			r_vector2f getRight();
			r_vector2f getUp();
	};
}

#endif