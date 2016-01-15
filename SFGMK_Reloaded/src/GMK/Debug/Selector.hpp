#ifndef SFGMKR_SELECTOR_HPP
#define SFGMKR_SELECTOR_HPP

#include "stdafx.h"

namespace gmk
{
	class Selector
	{
	public:

		enum eSELECTOR_STATE
		{
			STANDBY,
			SELECTION,
			SELECTED
		};

		Selector(GameObject* _gameObject);
		~Selector();

		r_void update(SFMLCanvas* _canvas);

		r_void onPhysicEnter();
		r_void onPhysicCollision(GameObject* _gameObject);
		r_void onPhysicExit();

		static r_void OnPhysicEnter(r_void* _selector);
		static r_void OnPhysicCollision(r_void* _selector, GameObject* _gameobject);
		static r_void OnPhysicExit(r_void* _selector);

		eSELECTOR_STATE getState();

	protected:

		GameObject* m_GameObject;

		r_void* m_PhysicFuncs;

		gmk::vector<GameObject*> m_SelectedObjects;

		eSELECTOR_STATE m_State;
		r_vector2f m_Start, m_End;
	};
}

#endif