/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		15/06/2015
	@brief		

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMK_SPHERE_COLLIDER_HPP
#define SFGMK_SPHERE_COLLIDER_HPP

#include "stdafx.h"

namespace gmk
{
	class SphereCollider : public Collider
	{
		public:

			SphereCollider(GameObject* _gameobject);
			~SphereCollider();

			r_float getRadius();
			r_float getSquaredRadius();
	};
}

#endif