#include "GameObject.hpp"
GameObject::GameObject()
	: name("GameObject")
{
	addComponent(new ComponentSprite(this));
}

GameObject::~GameObject()
{

}

void GameObject::update()
{
	for (unsigned int i = 0; i < m_Components.getElementNumber(); i++)
		m_Components[i]->OnUpdate();
}

void GameObject::draw()
{
	for (unsigned int i = 0; i < m_Components.getElementNumber(); i++)
		m_Components[i]->OnDraw();
}

void GameObject::OnUpdate()
{

}

void GameObject::OnDraw()
{

}

void GameObject::addComponent(GameObjectComponent* _component)
{
	m_Components.push_back(_component);
}

sfgmk::vector<GameObjectComponent*>& GameObject::getComponents()
{
	return m_Components;
}

void GameObject::showComponents(bool _value)
{
	for (unsigned int i = 0; i < m_Components.getElementNumber(); i++)
	{
		GameObjectComponent* component = m_Components[i];

		if (_value == true)
			component->OnPropertiesApparition();
		else
			component->OnPropertiesDisapparition();
	}
}