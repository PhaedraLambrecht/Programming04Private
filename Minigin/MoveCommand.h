#pragma once
#include "Command.h"
#include <glm/glm.hpp>

namespace dae
{
	class TransformComponent;
	class GameObject;

	class MoveCommand final : public BaseCommand
	{
	public:

		MoveCommand(GameObject* actor, glm::vec2 sirection, float moveSpeed);
		~MoveCommand() override;

		MoveCommand(const MoveCommand& other) = delete;
		MoveCommand(MoveCommand&& other) = delete;
		MoveCommand& operator=(const MoveCommand& other) = delete;
		MoveCommand& operator=(MoveCommand&& other) = delete;




		void Execute() override;


	private:

		TransformComponent* m_pTransform;
		GameObject* m_pActor;

		glm::vec2 m_Direction{};
		float m_MoveSpeed{};
	};
}

