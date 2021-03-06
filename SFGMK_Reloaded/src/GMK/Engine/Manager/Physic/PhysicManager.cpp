#include "stdafx.h"

namespace gmk
{
	PhysicManager::PhysicManager()
	{

	}

	PhysicManager::~PhysicManager()
	{
		m_PhysicObjects.clear();
	}

	void PhysicManager::update()
	{
		for (unsigned int i(0U); i < m_PhysicObjects.size(); i++)
		{
			Collider* collider = m_PhysicObjects[i];

			if (collider->isActive())
			{
				collider->setColliding(false);
				collider->updateCollidingWith();

				GameObject* gameobject = collider->getGameObject();
				if (!gameobject->networkProp)
					gameobject->onPhysicEnter();
			}
		}

		for( unsigned int i(0U); i < m_PhysicObjects.size(); i++ )
		{
			Collider* i_phys = m_PhysicObjects[i];

			if(i_phys->isActive())
			{
				GameObject* i_object = i_phys->getGameObject();

				for( unsigned int j(i + 1U); j < m_PhysicObjects.size(); j++ )
				{
					Collider* j_phys = m_PhysicObjects[j];

					if(j_phys->isActive())
					{
						GameObject* j_object = j_phys->getGameObject();

						if( testCollision(i_phys, j_phys) )
						{
							i_phys->setColliding(true);
							j_phys->setColliding(true);

							i_phys->addCollidingWith(j_phys);
							j_phys->addCollidingWith(i_phys);

							//Callbacks
							if (!i_object->networkProp)
								i_object->onPhysicCollision(j_object);

							if (!j_object->networkProp)
								j_object->onPhysicCollision(i_object);

							if (i_phys->beginCollidingWith(j_phys))
							{
								if (!i_object->networkProp)
									i_object->onPhysicCollisionEnter(j_object);

								if (!j_object->networkProp)
									j_object->onPhysicCollisionEnter(i_object);
							}
						}
					}
				}

				if (!i_object->networkProp)
					i_object->onPhysicExit();
			}
		}
	}

	void PhysicManager::draw(sf::RenderTarget* _render)
	{
		for( unsigned int i(0U); i < m_PhysicObjects.size(); i++ )
			m_PhysicObjects[i]->draw(_render);
	}

	void PhysicManager::addCollider(Collider* _NewCollider)
	{
		m_PhysicObjects.push_back(_NewCollider);
	}

	void PhysicManager::removeCollider(Collider* _ColliderToRemove)
	{
		m_PhysicObjects.removeElement(_ColliderToRemove);
	}

	bool PhysicManager::testCollision(Collider* _Collider1, Collider* _Collider2)
	{
		bool bCollision(false);
		eCOLLIDER_TYPE Type1 = _Collider1->getType(), Type2 = _Collider2->getType();

		GameObject* object1 = _Collider1->getGameObject();
		GameObject* object2 = _Collider2->getGameObject();

		//Si 2 shapes de m�me type
		if( Type1 == Type2 )
		{
			if( Type1 == eCOLLIDER_TYPE::eSphere )
				bCollision = collisionSphereSphere((SphereCollider*)_Collider1, (SphereCollider*)_Collider2, object1, object2);
			else if( Type1 == eCOLLIDER_TYPE::eOBB )
				bCollision = collisionObbObb((ObbCollider*)_Collider1, (ObbCollider*)_Collider2, object1, object2);
		}

		//Si shapes de types diff�rents
		else
		{
			bool bInverse = Type1 > Type2;

			if( (Type1 + Type2) == eSphere + eOBB )
				bInverse ? bCollision = collisionSphereObb((SphereCollider*)_Collider2, (ObbCollider*)_Collider1, object1, object2)
							: bCollision = collisionSphereObb((SphereCollider*)_Collider1, (ObbCollider*)_Collider2, object1, object2);
		}

		return bCollision;
	}

	bool PhysicManager::overlapBoxes(r_vector2f _Box1Center, r_vector2f _Box1HalfSize, r_vector2f _Box1Ortho[3], r_vector2f _Box2Center, r_vector2f _Box2HalfSize, r_vector2f _Box2Ortho[3])
	{
		//Calcul de T (vecteur entre les centres)
		r_vector2f T = _Box2Center - _Box1Center;

		//Extends
		float fRa(0.0f);
		float fRb(0.0f);

		//Tests axes Box1
		for( int i(0); i < 2; i++ )
		{
			fRa = _Box1HalfSize.x * ABS(math::DotProduct(_Box1Ortho[0], _Box1Ortho[i]))
				+ _Box1HalfSize.y * ABS(math::DotProduct(_Box1Ortho[1], _Box1Ortho[i]));

			fRb = _Box2HalfSize.x * ABS(math::DotProduct(_Box2Ortho[0], _Box1Ortho[i]))
				+ _Box2HalfSize.y * ABS(math::DotProduct(_Box2Ortho[1], _Box1Ortho[i]));

			if( ABS(math::DotProduct(T, _Box1Ortho[i])) > fRa + fRb )
				return false;
		}

		//Tests axes Box2
		for( int i(0); i < 2; i++ )
		{
			fRa = _Box1HalfSize.x * ABS(math::DotProduct(_Box1Ortho[0], _Box2Ortho[i]))
				+ _Box1HalfSize.y * ABS(math::DotProduct(_Box1Ortho[1], _Box2Ortho[i]));

			fRb = _Box2HalfSize.x * ABS(math::DotProduct(_Box2Ortho[0], _Box2Ortho[i]))
				+ _Box2HalfSize.y * ABS(math::DotProduct(_Box2Ortho[1], _Box2Ortho[i]));

			if( ABS(math::DotProduct(T, _Box2Ortho[i])) > fRa + fRb )
				return false;
		}

		//Tests combinaisons d'axes
		r_vector2f L;

		for( int i(0); i < 2; i++ )
		{
			for( int j(0); j < 2; j++ )
			{
				//Construction de l'axe 
				L = math::CrossProduct(_Box1Ortho[i], _Box2Ortho[j]);

				//Test
				fRa = _Box1HalfSize.x * ABS(math::DotProduct(_Box1Ortho[0], L))
					+ _Box1HalfSize.y * ABS(math::DotProduct(_Box1Ortho[1], L));

				fRb = _Box2HalfSize.x * ABS(math::DotProduct(_Box2Ortho[0], L))
					+ _Box2HalfSize.y * ABS(math::DotProduct(_Box2Ortho[1], L));

				if( ABS(math::DotProduct(T, L)) > fRa + fRb )
					return false;
			}
		}

		return true;
	}

	bool PhysicManager::collisionSphereSphere(SphereCollider* _Collider1, SphereCollider* _Collider2, GameObject* _object1, GameObject* _object2)
	{
		float fDistanceSquared = math::Calc_DistanceSquared(_Collider1->getGameObject()->getCenter() + _Collider1->getOffset(), _Collider2->getGameObject()->getCenter() + _Collider2->getOffset());

		float fRadiusSquared = _Collider1->getRadius() + _Collider2->getRadius();
		fRadiusSquared *= fRadiusSquared;

		return fDistanceSquared < fRadiusSquared;
	}

	bool PhysicManager::collisionObbObb(ObbCollider* _Collider1, ObbCollider* _Collider2, GameObject* _object1, GameObject* _object2)
	{
		if (math::Calc_DistanceSquared(_Collider1->getGameObject()->getCenter(), _Collider2->getGameObject()->getCenter()) > (_Collider1->getSquaredRadius() + _Collider2->getSquaredRadius()))
			return false;

		//Donn�es boite 1
		r_vector2f Box1Center = _Collider1->getGameObject()->getCenter();
		r_vector2f Box1HalfSize = _Collider1->getWorldSize() * 0.5f;

		r_vector2f Box1Ortho[2];
		Box1Ortho[0] = math::Calc_UnitVector(_Collider1->getRight());
		Box1Ortho[1] = math::Calc_UnitVector(_Collider1->getUp());

		//Donn�es boite 2
		r_vector2f Box2Center = _Collider2->getGameObject()->getCenter();
		r_vector2f Box2HalfSize = _Collider2->getWorldSize() * 0.5f;

		r_vector2f Box2Ortho[2];
		Box2Ortho[0] = math::Calc_UnitVector(_Collider2->getRight());
		Box2Ortho[1] = math::Calc_UnitVector(_Collider2->getUp());

		//Test collision
		return overlapBoxes(Box1Center, Box1HalfSize, Box1Ortho, Box2Center, Box2HalfSize, Box2Ortho);
	}

	bool PhysicManager::collisionSphereObb(SphereCollider* _SphereCollider, ObbCollider* _BoxCollider, GameObject* _object1, GameObject* _object2)
	{
		r_float radius = _SphereCollider->getRadius() + _BoxCollider->getRadius();

		if (math::Calc_DistanceSquared(_SphereCollider->getGameObject()->getCenter(), _BoxCollider->getGameObject()->getCenter()) > (radius * radius))
			return false;

		float fSphereRadius(_SphereCollider->getRadius()), fDifference(0.0f), fDistance(0.0);
		r_vector2f Scale = _BoxCollider->getGameObject()->transform.getScale();
		r_vector2f MinVector(_BoxCollider->getMin()), MaxVector(_BoxCollider->getMax());
		r_vector2f NewSphereCenter;

		//Transform sphere center from world coordinates to OBB coordinates
		NewSphereCenter = _BoxCollider->getGameObject()->transform.getInverseTransform().transformPoint(_SphereCollider->getGameObject()->getCenter());

		//X
		if( NewSphereCenter.x < MinVector.x )
		{
			fDifference = (NewSphereCenter.x - MinVector.x) * Scale.x;
			fDistance += fDifference * fDifference;
		}
		else if( NewSphereCenter.x > MaxVector.x )
		{
			fDifference = (NewSphereCenter.x - MaxVector.x) * Scale.x;
			fDistance += fDifference * fDifference;
		}

		//Y
		if( NewSphereCenter.y < MinVector.y )
		{
			fDifference = (NewSphereCenter.y - MinVector.y) * Scale.y;
			fDistance += fDifference * fDifference;
		}
		else if( NewSphereCenter.y > MaxVector.y )
		{
			fDifference = (NewSphereCenter.y - MaxVector.y) * Scale.y;
			fDistance += fDifference * fDifference;
		}

		return fDistance <= fSphereRadius * fSphereRadius;
	}
}