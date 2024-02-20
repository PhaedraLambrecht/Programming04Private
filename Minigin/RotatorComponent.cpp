#include "RotatorComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "Time.h"
#include <iostream>


namespace dae
{
	RotatorComponent::RotatorComponent(GameObject* Owner)
		:BaseComponent(Owner)
		,m_Radius{}
		,m_RotationSpeed{}
		,m_CurrAngle{}
	{
		if (GetOwner()->HasComponent<TransformComponent>())
		{
			m_pTransform = GetOwner()->GetComponent<TransformComponent>();
		}
		else
		{
			m_pTransform = nullptr;
		}

	}

	RotatorComponent::~RotatorComponent()
	{
		std::cout << "RotatorComponent\n";
	}


	void RotatorComponent::Update()
	{
		auto nextAngle = m_CurrAngle + m_RotationSpeed * Time::GetInstance().GetDeltaTime();
		if (nextAngle != m_CurrAngle)
		{
			m_CurrAngle = nextAngle;

			const float x{ cosf(m_CurrAngle) * m_Radius };
			const float y{ sinf(m_CurrAngle) * m_Radius };
			m_pTransform->SetPosition(x, y, 0.0f);
		}
	}

	void RotatorComponent::SetRotationpeed(float speed)
	{
		m_RotationSpeed = speed;
	}

	void RotatorComponent::setRadius(float radius)
	{
		m_Radius = radius;
	}
}