#include "TextRenderComponent.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include <stdexcept>


namespace dae
{
	TextRenderComponent::TextRenderComponent(GameObject* Owner)
		:BaseComponent(Owner)
	{
		m_pText = GetOwner()->GetComponent<TextComponent>();
		m_pTransform = GetOwner()->GetComponent<TransformComponent>();
	}

	TextRenderComponent::~TextRenderComponent()
	{
		delete m_pText;
		m_pText = nullptr;

		delete m_pTransform;
		m_pTransform = nullptr;
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
