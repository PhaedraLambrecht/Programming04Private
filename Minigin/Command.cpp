#include "Command.h"
#include "GameObject.h"


dae::Command::Command(GameObject* pActor)
	:m_pActor{pActor}
{
}

dae::GameObject* dae::Command::GetActor() const
{
	return m_pActor;
}
