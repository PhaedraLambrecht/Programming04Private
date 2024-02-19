#pragma once
#include "BaseComponent.h"
#include <SDL_pixels.h>
#include <string>
#include <memory>


namespace dae
{
	class Font;
	class Texture2D;

	class TextComponent final : public BaseComponent
	{
	public:

		TextComponent(GameObject* Owner);
		~TextComponent() override;

		// Copy and move
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;



		void SetText(std::string& text);
		void SetFont(std::shared_ptr<Font> font);
		void SetColor(const SDL_Color color);

		std::shared_ptr<Texture2D> GetTexture() const;


	private:

		void SetTexture();

		std::string m_Text;
		SDL_Color m_Color;
		std::shared_ptr<Font> m_pFont;
		std::shared_ptr<Texture2D> m_pTexture;
	};
}

