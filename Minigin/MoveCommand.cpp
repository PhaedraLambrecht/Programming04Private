#include "MoveCommand.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Time.h"


dae::MoveCommand::MoveCommand(GameObject* actor)
	:Command(actor)
{

	m_pTransform = GetActor()->GetComponent<TransformComponent>();
}


void dae::MoveCommand::Execute()
{
	glm::vec2 position{ m_pTransform->GetLocalPosition() + m_Direction * m_MoveSpeed * Time::GetInstance().GetDeltaTime() };
	m_pTransform->SetLocalPosition(position.x, position.y);
}

void dae::MoveCommand::SetDirection(glm::vec2 direction)
{
	m_Direction = direction;
}

void dae::MoveCommand::SetMoveSpeed(float moveSpeed)
{
	m_MoveSpeed = moveSpeed;
}

