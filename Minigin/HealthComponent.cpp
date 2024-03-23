#include "HealthComponent.h"
#include "EventManager.h"
#include <iostream>


dae::HealthComponent::HealthComponent(GameObject* owner)
	:BaseComponent(owner)
	,m_Health{1}
	,m_PlayerIndex{0}
{
}

dae::HealthComponent::~HealthComponent()
{
	std::cout << "HealthComponent\n";
}


void dae::HealthComponent::Damaged(float damage)
{
	m_Health -= damage;

	if (m_Health <= 0)
	{
		Death();
	}
}

void dae::HealthComponent::SetPlayerIndex(unsigned playerIndex)
{
	m_PlayerIndex = playerIndex;
}

void dae::HealthComponent::Death()
{
	std::unique_ptr<PlayerEvent> event = std::make_unique<PlayerEvent>("Death", m_PlayerIndex);
	EventManager::GetInstance().QueueEvent<PlayerEvent>(std::move(event));
}