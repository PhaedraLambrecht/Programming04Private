#pragma once
#include "BaseComponent.h"
#include <string>
#include <memory>


namespace dae
{
	class Texture2D;

	class ImageComponent final : public BaseComponent
	{
	public:

		ImageComponent(GameObject* Owner);
		~ImageComponent() override;

		// Copy and move
		ImageComponent(const ImageComponent& other) = delete;
		ImageComponent(ImageComponent&& other) = delete;
		ImageComponent& operator=(const ImageComponent& other) = delete;
		ImageComponent& operator=(ImageComponent&& other) = delete;



		void SetTexture(const std::string& fileName);
		std::shared_ptr<Texture2D> GetTexture() const;


	private:

		std::shared_ptr<Texture2D> m_pTexture;
	};
}


