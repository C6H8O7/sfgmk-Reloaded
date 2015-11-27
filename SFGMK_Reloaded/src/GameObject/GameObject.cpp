#include "GameObject.hpp"
GameObject::GameObject()
	: name("GameObject")
{

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