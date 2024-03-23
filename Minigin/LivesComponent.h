#pragma once
#include "BaseComponent.h"
#include "Event.h"


namespace dae
{
	class GameObject;
	class TextComponent;


	class LivesComponent final : public BaseComponent
	{
	public:

		LivesComponent(GameObject* owner);
		~LivesComponent();
		
		LivesComponent(const LivesComponent& other) = delete;
		LivesComponent(LivesComponent&& other) = delete;
		LivesComponent& operator=(const LivesComponent& other) = delete;
		LivesComponent& operator=(LivesComponent&& other) = delete;




		void SetPlayerIndex(unsigned playerIndex);


	private:

		void UpdateText();
		void Death(const Event* e);


		unsigned m_PlayerIndex;
		int m_LivesLeft;
		TextComponent* m_pTextComponent;
	};

}
