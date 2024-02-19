#include "TransformComponent.h"
#include <iostream>


namespace dae
{
	TransformComponent::TransformComponent(GameObject* Owner)
		:BaseComponent(Owner)
		,m_Position{}
	{
	}

	TransformComponent::~TransformComponent()
	{
		std::cout << "TransformComponent\n";
	}


	const glm::vec3& TransformComponent::GetPosition() const
	{
		return m_Position;
	}

	void TransformComponent::SetPosition(float x, float y, float z)
	{
		m_Position.x = x;
		m_Position.y = y;
		m_Position.z = z;
	}
}

