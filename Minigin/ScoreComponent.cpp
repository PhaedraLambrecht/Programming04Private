#include "ScoreComponent.h"
#include "TextComponent.h"
#include "EventManager.h"
#include "Event.h"
#include "GameObject.h"
#include "Achievements.h"
#include <stdexcept>
#include <iostream>

dae::ScoreComponent::ScoreComponent(GameObject* owner)
	:BaseComponent(owner)
	, m_RewardAmount{100}
	,m_PointsEarned{0}
	,m_PlayerIndex{0}
	,m_AchievementPoints{1000}
{

	if (GetOwner()->HasComponent<TextComponent>())
	{
		m_pTextComponent = GetOwner()->GetComponent<TextComponent>();
	}
	else
	{
		m_pTextComponent = GetOwner()->AddComponent<TextComponent>();
	}


	UpdateText();


	// Define a lambda function to bind the EarnPoints member function to an event observer
	auto boundLoseLife = [this](const Event* event)
	{
		// Call the EarnPoints member function of the ScoreComponent object with the event argument passed by the event manager
		this->UpdateScore(event);
	};

	PlayerEvent event{ "EnemyDeath", m_PlayerIndex };
	EventManager::GetInstance().RegisterObserver(event, boundLoseLife);
}

dae::ScoreComponent::~ScoreComponent()
{
	std::cout << "ScoreComponent\n";
}


void dae::ScoreComponent::SetPlayerIndex(unsigned playerIndex)
{
	m_PlayerIndex = playerIndex;
}

void dae::ScoreComponent::LinkAchievements(const std::shared_ptr<Achievements>& gameAchievements)
{
	m_GameAchievements = gameAchievements;
}

void dae::ScoreComponent::UpdateText()
{
	std::string text = "Player: " + std::to_string(m_PlayerIndex) + " - score: " + std::to_string(m_PointsEarned);
	m_pTextComponent->SetText(text);
}

void dae::ScoreComponent::UpdateScore(const Event* e)
{
	if (strcmp(e->eventType, "EnemyDeath") == 0)
	{
		const PlayerEvent* playerEvent = dynamic_cast<const PlayerEvent*>(e);
		if (playerEvent && playerEvent->playerIndex == m_PlayerIndex)
		{
			m_PointsEarned += m_RewardAmount;
			UpdateText();
		
		}
	}

	CheckForAchievements();
}

void dae::ScoreComponent::CheckForAchievements()
{
	if (m_AchievementPoints <= m_PointsEarned)
	{
		bool hasAchieved;

		m_GameAchievements->HasReceivedAchievement(hasAchieved);
		if (!hasAchieved)
		{
			m_GameAchievements->SetAchievement();
		}
	}
}
