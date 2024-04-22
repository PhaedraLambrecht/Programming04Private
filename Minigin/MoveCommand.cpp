#include "MoveCommand.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "GameTime.h"
#include <iostream>

dae::MoveCommand::MoveCommand(GameObject* actor, glm::vec2 direction, float moveSpeed)
	:m_pActor{ actor }
	,m_Direction{direction}
	,m_MoveSpeed{moveSpeed}
{
	if (actor->HasComponent<TransformComponent>())
	{
		m_pTransform = actor->GetComponent<TransformComponent>();
	}
	else
	{
		m_pTransform = nullptr;
	}
}

dae::MoveCommand::~MoveCommand()
{
	std::cout << "MoveCommand\n";
}


void dae::MoveCommand::Execute()
{
	glm::vec2 position{ m_pTransform->GetLocalPosition() + m_Direction * m_MoveSpeed * GameTime::GetInstance().GetDeltaTime() };
	m_pTransform->SetLocalPosition(position.x, position.y);
}
