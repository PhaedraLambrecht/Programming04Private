#pragma once
#include "Command.h"


namespace dae
{
	class GameObject;
	class AddPointsComponnent;

	class AddPointsCommand final : public BaseCommand
	{
	public:

		AddPointsCommand(GameObject* actor);
		~AddPointsCommand() override;

		AddPointsCommand(const AddPointsCommand& other) = delete;
		AddPointsCommand(AddPointsCommand&& other) = delete;
		AddPointsCommand& operator=(const AddPointsCommand& other) = delete;
		AddPointsCommand& operator=(AddPointsCommand&& other) = delete;




		void Execute() override;


	private:

		AddPointsComponnent* m_pAddPointsComponnent;
		float m_Damage;
	};
}
