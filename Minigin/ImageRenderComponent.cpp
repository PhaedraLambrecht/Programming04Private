#include "ImageRenderComponent.h"
#include "ImageComponent.h"
#include "TransformComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include <stdexcept>


namespace dae
{
	ImageRenderComponent::ImageRenderComponent(GameObject* Owner)
		:BaseComponent(Owner)
	{
		m_pImage = GetOwner()->GetComponent<ImageComponent>();
		m_pTransform = GetOwner()->GetComponent<TransformComponent>();
	}

	ImageRenderComponent::~ImageRenderComponent()
	{
		delete m_pImage;
		m_pImage = nullptr;

		delete m_pTransform;
		m_pTransform = nullptr;
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