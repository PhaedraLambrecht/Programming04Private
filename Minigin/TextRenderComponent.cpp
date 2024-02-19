#include "TextRenderComponent.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include <stdexcept>
#include <iostream>

namespace dae
{
	TextRenderComponent::TextRenderComponent(GameObject* Owner)
		:BaseComponent(Owner)
	{
		m_pText = GetOwner()->AddComponent<TextComponent>();
		m_pTransform = GetOwner()->AddComponent<TransformComponent>();
	}

	TextRenderComponent::~TextRenderComponent()
	{
		std::cout << "TextRenderComponent\n";
	}


	void TextRenderComponent::Render() const
	{
		if (!m_pText)
		{
			throw std::invalid_argument("TextRendererComponent needs a TextComponent");
		}

		if (!m_pTransform)
		{
			throw std::invalid_argument("TextRendererComponent needs a TransformComponent");
		}
	
		
		const auto& position = m_pTransform->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pText->GetTexture(), position.x, position.y);
	}
}
