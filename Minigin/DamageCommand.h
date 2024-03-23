#pragma once
#include "Command.h"


namespace dae
{
	class HealthComponent;
	class GameObject;

	class DamageCommand : public BaseCommand
	{
	public:

		DamageCommand(GameObject* actor, float damage);
		~DamageCommand() override;

		DamageCommand(const DamageCommand& other) = delete;
		DamageCommand(DamageCommand&& other) = delete;
		DamageCommand& operator=(const DamageCommand& other) = delete;
		DamageCommand& operator=(DamageCommand&& other) = delete;




		void Execute() override;


	private:


		HealthComponent* m_pHealthComponnent;
		float m_Damage;
	};
}


