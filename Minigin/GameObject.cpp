#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <iostream>


dae::GameObject::GameObject()
{
	m_pTransform = AddComponent<TransformComponent>();
}

dae::GameObject::~GameObject()
{
	std::cout << "\nGameObject\n";
}


void dae::GameObject::Update()
{
	// todo: easiest way to fix dead objects is walking trough the loop backwards
	for (const auto& component : m_pComponents)
	{
		component->Update();
	}
}

void dae::GameObject::Render() const
{
	for (const auto& component : m_pComponents)
	{
		component->Render();
	}
}