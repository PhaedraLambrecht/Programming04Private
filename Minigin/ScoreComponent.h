#pragma once
#include "BaseComponent.h"
#include "Event.h"
#include <memory>


namespace dae
{

	class GameObject;
	class TextComponent;
	class Achievements;

	class ScoreComponent final : public BaseComponent
	{
	public:

		ScoreComponent(GameObject* owner);
		~ScoreComponent();


		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;




		void SetPlayerIndex(unsigned playerIndex);
		void LinkAchievements(const std::shared_ptr<Achievements>& gameAchievements);


	private:

		void UpdateText();
		void UpdateScore(const Event* e);
		void CheckForAchievements();

		const int m_AchievementPoints;

		const int m_RewardAmount;
		unsigned int m_PlayerIndex;
		int m_PointsEarned;

		TextComponent* m_pTextComponent;
		std::shared_ptr<Achievements> m_GameAchievements;
	};
}


