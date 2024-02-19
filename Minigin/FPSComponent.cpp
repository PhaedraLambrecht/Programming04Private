#include "FPSComponent.h"
#include "TextComponent.h"
#include "Time.h"
#include "GameObject.h"
#include <stdexcept>


namespace dae
{
	FPSComponent::FPSComponent(GameObject* Owner)
		:BaseComponent(Owner)
		,m_fps{}
	{
		m_pText = GetOwner()->GetComponent<TextComponent>();
	}

	FPSComponent::~FPSComponent()
	{
		delete m_pText;
		m_pText = nullptr;
	}


	void FPSComponent::Update()
	{
		if (!m_pText)
		{
			throw std::invalid_argument("FPSComponent needs a TextComponent");
		}

		float calculatedFPS = 1.0f / Time::GetInstance().GetDeltaTime();

		if (calculatedFPS != m_fps)
		{
			m_fps = calculatedFPS;
			std::string fpsText = std::to_string((int)m_fps) + "FPS"; // todo: Look into what caused the issue that this can't be in the line below.
			m_pText->SetText(fpsText); 
		}
	}
}