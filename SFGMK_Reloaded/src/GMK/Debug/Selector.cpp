#include "stdafx.h"

namespace gmk
{
	Selector::Selector(GameObject* _gameObject)
		: m_GameObject(_gameObject)
	{
		m_PhysicFuncs = new GameObject::sGAMEOBJECT_PHYSICFUNCS();

		GameObject::sGAMEOBJECT_PHYSICFUNCS* phys = (GameObject::sGAMEOBJECT_PHYSICFUNCS*)m_PhysicFuncs;

		phys->enter = &Selector::OnPhysicEnter;
		phys->collision = &Selector::OnPhysicCollision;
		phys->exit = &Selector::OnPhysicExit;

		phys->object = this;

		m_GameObject->addPhysicFuncs(phys);
	}

	Selector::~Selector()
	{
		GameObject::sGAMEOBJECT_PHYSICFUNCS* phys = (GameObject::sGAMEOBJECT_PHYSICFUNCS*)m_PhysicFuncs;

		m_GameObject->removePhysicFuncs(phys);

		delete phys;
	}

	r_void Selector::update(SFMLCanvas* _canvas)
	{
		gmk::Mouse& mouse = _canvas->getInputManager()->getMouse();

		sf::Vector2f mouse_pos = mouse.getWorldPosition();

		switch (mouse.getButtonState(sf::Mouse::Left))
		{
			case KEY_PRESSED:
				m_Start = mouse_pos;
				m_State = eSELECTOR_STATE::SELECTION;
				break;

			case KEY_RELEASED:
				m_State = eSELECTOR_STATE::SELECTED;
				break;

			case KEY_UP:
				m_State = eSELECTOR_STATE::STANDBY;
				break;
		}

		switch (m_State)
		{
			case eSELECTOR_STATE::SELECTION:
				m_End = mouse_pos;
				if (m_Start == m_End)
				{
					m_Start += sf::Vector2f(-1.0f, -1.0f);
					m_End += sf::Vector2f(1.0f, 1.0f);
				}
				break;

			case eSELECTOR_STATE::SELECTED:
				break;

			case eSELECTOR_STATE::STANDBY:
				m_Start = m_End;
				break;
		}

		r_vector2f scale = m_End - m_Start;
		scale.x = ABS(scale.x);
		scale.y = ABS(scale.y);

		r_vector2f pos;
		pos.x = MIN(m_Start.x, m_End.x);
		pos.y = MIN(m_Start.y, m_End.y);

		m_GameObject->transform.position = pos;
		m_GameObject->transform.scale = scale;
	}

	r_void Selector::onPhysicEnter()
	{
		if (m_State == eSELECTOR_STATE::SELECTION)
		{
			for (r_uint32 i = 0; i < m_SelectedObjects.size(); i++)
				m_SelectedObjects[i]->debug.selected = false;

			m_SelectedObjects.clear();
		}
	}

	r_void Selector::onPhysicCollision(GameObject* _gameObject)
	{
		if (m_State == eSELECTOR_STATE::SELECTION)
		{
			m_SelectedObjects.push_back(_gameObject);
			_gameObject->debug.selected = true;
		}
	}

	r_void Selector::onPhysicExit()
	{

	}

	r_void Selector::OnPhysicEnter(r_void* _selector)
	{
		((Selector*)_selector)->onPhysicEnter();
	}

	r_void Selector::OnPhysicCollision(r_void* _selector, GameObject* _gameobject)
	{
		((Selector*)_selector)->onPhysicCollision(_gameobject);
	}

	r_void Selector::OnPhysicExit(r_void* _selector)
	{
		((Selector*)_selector)->onPhysicExit();
	}

	Selector::eSELECTOR_STATE Selector::getState()
	{
		return m_State;
	}
}