#include "TextComponent.h"
#include "Font.h"
#include "Texture2D.h"
#include "Renderer.h"
#include <SDL_ttf.h>
#include <stdexcept>
#include <iostream>


namespace dae
{
	TextComponent::TextComponent(GameObject* Owner)
		:BaseComponent(Owner)
		,m_Text{"Default"}
		,m_Color{}
		,m_pFont{}
		,m_pTexture{nullptr}
	{
	}

	TextComponent::~TextComponent()
	{
		std::cout << "TextComponent\n";
	}


	void TextComponent::SetText(std::string& text)
	{
		m_Text = text;
		SetTexture();
	}

	void TextComponent::SetFont(std::shared_ptr<Font> font)
	{
		m_pFont = std::move(font);
		SetTexture();
	}

	void TextComponent::SetColor(const SDL_Color color)
	{
		m_Color = color;
		SetTexture();
	}

	std::shared_ptr<Texture2D> TextComponent::GetTexture() const
	{
		return m_pTexture;
	}

	void TextComponent::SetTexture()
	{
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_Color);
		if (!surf)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}

		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (!texture)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}


		SDL_FreeSurface(surf);
		m_pTexture = std::make_shared<Texture2D>(texture);
	}

}
