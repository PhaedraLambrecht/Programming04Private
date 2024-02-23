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
		if (GetOwner()->HasComponent<TextComponent>())
		{
			m_pText = GetOwner()->GetComponent<TextComponent>();
		}
		else
		{
			m_pText = GetOwner()->AddComponent<TextComponent>();
		}
	
		if (GetOwner()->HasComponent<TransformComponent>())
		{
			m_pTransform = GetOwner()->GetComponent<TransformComponent>();
		}
		else
		{
			m_pTransform = nullptr;
		}
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
	
		
		const auto& position = m_pTransform->GetLocalPosition();
		Renderer::GetInstance().RenderTexture(*m_pText->GetTexture(), position.x, position.y);
	}
}
