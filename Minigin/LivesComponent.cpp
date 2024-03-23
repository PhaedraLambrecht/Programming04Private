#include "LivesComponent.h"
#include "EventManager.h"
#include "TextComponent.h"
#include "GameObject.h"
#include <memory>
#include <iostream>


dae::LivesComponent::LivesComponent(GameObject* owner)
	:BaseComponent(owner)
	,m_LivesLeft{3}
	,m_PlayerIndex{0}
{
	if (GetOwner()->HasComponent<TextComponent>())
	{
		m_pTextComponent = GetOwner()->GetComponent<TextComponent>();
	}
	else
	{
		m_pTextComponent = nullptr;
	}


	UpdateText();


	// Define a lambda function to bind the LoseLife member function to an event observer
	auto boundLoseLife = [this](const Event* event)
	{
		// Call the LoseLife member function of the LivesComponent object with the event argument passed by the event manager
		this->Death(event);
	};
	PlayerEvent event{"Death", m_PlayerIndex};
	EventManager::GetInstance().RegisterObserver(event, boundLoseLife);
}

dae::LivesComponent::~LivesComponent()
{
	std::cout << "LivesComponent\n";
}


void dae::LivesComponent::SetPlayerIndex(unsigned playerIndex)
{
	m_PlayerIndex = playerIndex;
}

void dae::LivesComponent::UpdateText()
{
	std::string text = "Player: " + std::to_string(m_PlayerIndex) + " - Lives: " + std::to_string(m_LivesLeft);
	m_pTextComponent->SetText(text);
}

void dae::LivesComponent::Death(const Event* e)
{
	if (m_LivesLeft <= 0)
	{
		std::cout << "Dead\n";
		return;
	}

	if (strcmp(e->eventType, "Death") == 0)
	{
		const PlayerEvent* playerEvent = dynamic_cast<const PlayerEvent*>(e);
		if (playerEvent && playerEvent->playerIndex == m_PlayerIndex)
		{
			m_LivesLeft -= 1;
			UpdateText();

		}
	}

}
