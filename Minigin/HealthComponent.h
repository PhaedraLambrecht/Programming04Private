#pragma once
#include "BaseComponent.h"

namespace dae
{
	class HealthComponent final : public BaseComponent
	{
	public:

		HealthComponent(GameObject* owner);
		~HealthComponent();
		
		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;




		void SetPlayerIndex(unsigned playerIndex);
		void Damaged(float damage);


	private:

		void Death();
	

		float m_Health;
		unsigned m_PlayerIndex;
	};
}


