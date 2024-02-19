#include "ImageRenderComponent.h"
#include "ImageComponent.h"
#include "TransformComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include <stdexcept>
#include <iostream>


namespace dae
{
	ImageRenderComponent::ImageRenderComponent(GameObject* Owner)
		:BaseComponent(Owner)
	{
		m_pImage = GetOwner()->AddComponent<ImageComponent>();
		m_pTransform = GetOwner()->AddComponent<TransformComponent>();
	}

	ImageRenderComponent::~ImageRenderComponent()
	{
		std::cout << "ImageRenderComponent\n";
	}


	void ImageRenderComponent::Render() const
	{
		if (!m_pImage)
		{
			throw std::invalid_argument("ImageRenderComponent needs a ImageComponent");
		}

		if (!m_pTransform)
		{
			throw std::invalid_argument("TextRendererComponent needs a TransformComponent");
		}


		const auto& position = m_pTransform->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pImage->GetTexture(), position.x, position.y);
	}
}