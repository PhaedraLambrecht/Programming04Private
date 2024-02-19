#pragma once
#include "BaseComponent.h"


namespace dae
{
	class TextComponent;
	class TransformComponent;

	class TextRenderComponent final : public BaseComponent
	{
	public:

		TextRenderComponent(GameObject* Owner);
		~TextRenderComponent() override;

		// Copy and move
		TextRenderComponent(const TextRenderComponent& other) = delete;
		TextRenderComponent(TextRenderComponent&& other) = delete;
		TextRenderComponent& operator=(const TextRenderComponent& other) = delete;
		TextRenderComponent& operator=(TextRenderComponent&& other) = delete;



		void Render() const override;


	private:

		TextComponent* m_pText;
		TransformComponent* m_pTransform;
	};
}

