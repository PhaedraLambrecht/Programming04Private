#include "RotatorComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "Time.h"
#define _USE_MATH_DEFINES
#include <math.h>
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
		float pi{ float(M_PI) };
		
		auto nextAngle = m_CurrAngle + m_RotationSpeed * Time::GetInstance().GetDeltaTime() / pi;
		if (nextAngle != m_CurrAngle)
		{
			m_CurrAngle = nextAngle;
			
			if (GetOwner()->GetParent())
			{
				// If you have a parent, take their worldposition add the angle multiplied by the radius
				const float x{ GetOwner()->GetParent().get()->GetTransform().GetWorldPosition().x + cosf(m_CurrAngle) * m_Radius };
				const float y{ GetOwner()->GetParent().get()->GetTransform().GetWorldPosition().y + sinf(m_CurrAngle) * m_Radius };
				m_pTransform->SetLocalPosition(x, y);
			}
			else
			{
				// otherwise, get your position 
				const float x{ m_pTransform->GetLocalPosition().x + cosf(m_CurrAngle) * m_Radius };
				const float y{ m_pTransform->GetLocalPosition().y + sinf(m_CurrAngle) * m_Radius };
				m_pTransform->SetLocalPosition(x, y);
			}

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