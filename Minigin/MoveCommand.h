#pragma once
#include "Command.h"
#include <glm/glm.hpp>

namespace dae
{
	class TransformComponent;
	class MoveCommand final : public Command
	{
	public:

		MoveCommand(GameObject* actor);
		~MoveCommand() override = default;

		MoveCommand(const MoveCommand& other) = delete;
		MoveCommand(MoveCommand&& other) = delete;
		MoveCommand& operator=(const MoveCommand& other) = delete;
		MoveCommand& operator=(MoveCommand&& other) = delete;


		void Execute() override;

		void SetDirection(glm::vec2 direction);
		void SetMoveSpeed(float moveSpeed);


	private:

		TransformComponent* m_pTransform;

		glm::vec2 m_Direction{};
		float m_MoveSpeed{};
	};
}

