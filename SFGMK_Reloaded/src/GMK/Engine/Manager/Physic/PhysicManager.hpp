/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		15/06/2015
	@brief		Manager de la physique, gére les collisions/réponses aux collisions

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMKR_PHYSIC_MANAGER_HPP
#define SFGMKR_PHYSIC_MANAGER_HPP

#include "stdafx.h"

namespace gmk
{
	class PhysicManager : public SingletonTemplate<PhysicManager>
	{
		friend class SingletonTemplate<PhysicManager>;

		private:

			gmk::vector<Collider*> m_PhysicObjects;

			PhysicManager();
			~PhysicManager();

		public:

			void update();

			void draw(sf::RenderTarget* _render);

			void addCollider(Collider* _NewCollider);
			void removeCollider(Collider* _ColliderToRemove);

			bool testCollision(Collider* _Collider1, Collider* _Collider2);

			bool overlapBoxes(r_vector2f _Box1Center, r_vector2f _Box1HalfSize, r_vector2f _Box1Ortho[3], r_vector2f _Box2Center, r_vector2f _Box2HalfSize, r_vector2f _Box2Ortho[3]);

			bool collisionSphereSphere(SphereCollider* _Collider1, SphereCollider* _Collider2, GameObject* _object1, GameObject* _object2);
			bool collisionObbObb(ObbCollider* _Collider1, ObbCollider* _Collider2, GameObject* _object1, GameObject* _object2);

			bool collisionSphereObb(SphereCollider* _SphereCollider, ObbCollider* _BoxCollider, GameObject* _object1, GameObject* _object2);
	};
}


#endif