#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"

#include "GameObject.h"
#include "ImageComponent.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "ImageRenderComponent.h"
#include "TextRenderComponent.h"
#include "FPSComponent.h"


void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");


	// Background
	const auto backGroundImage = std::make_shared<dae::GameObject>();
	backGroundImage->AddComponent<dae::ImageComponent>();
	backGroundImage->AddComponent<dae::TransformComponent>();
	backGroundImage->AddComponent<dae::ImageRenderComponent>();
	backGroundImage->GetComponent<dae::ImageComponent>()->SetTexture("background.tga");

	scene.Add(backGroundImage);


	const auto font{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 25) };
	
	// Title
	{
		const SDL_Color tittleColor{ 255, 255, 255 };
		std::string text = "Programming 4 Assignment";
		
		const auto title = std::make_shared<dae::GameObject>();
		title->AddComponent<dae::TextComponent>();
		title->AddComponent<dae::TransformComponent>();
		title->AddComponent<dae::TextRenderComponent>();
		title->GetComponent<dae::TextComponent>()->SetFont(font);
		title->GetComponent<dae::TextComponent>()->SetColor(tittleColor);
		title->GetComponent<dae::TextComponent>()->SetText(text);

		scene.Add(title);
	}




	//go = std::make_shared<dae::GameObject>();
	//go->SetTexture("logo.tga");
	//go->SetPosition(216, 180);
	//scene.Add(go);

	//auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//auto to = std::make_shared<dae::TextObject>("Programming 4 Assignment", font);
	//to->SetPosition(80, 20);
	//scene.Add(to);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}