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
#include "RotatorComponent.h"

#include "CacheComponent.h"


#include "InputManager.h"
#include "Controller.h"
#include "MoveCommand.h"

#include <iostream>

dae::Minigin m_Engine("../Data/");


void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	const auto font{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 25) };


	// Background
	{
		const auto backGroundImage = std::make_shared<dae::GameObject>();
		backGroundImage->AddComponent<dae::ImageComponent>();
		backGroundImage->AddComponent<dae::ImageRenderComponent>();

		backGroundImage->GetComponent<dae::ImageComponent>()->SetTexture("background.tga");


		scene.Add(backGroundImage);
	}


	// Title
	{
		const SDL_Color tittleColor{ 255, 255, 255 };
		std::string text = "Programming 4 Assignment - W03";


		const auto title = std::make_shared<dae::GameObject>();
		title->AddComponent<dae::TextComponent>();
		title->AddComponent<dae::TextRenderComponent>();

		title->GetComponent<dae::TextComponent>()->SetFont(font);
		title->GetComponent<dae::TextComponent>()->SetColor(tittleColor);
		title->GetComponent<dae::TextComponent>()->SetText(text);
		title->GetComponent<dae::TransformComponent>()->SetLocalPosition(120.0f, 30.0f);


		scene.Add(title);
	}


	// DAE Image
	{
		const auto daeImage = std::make_shared<dae::GameObject>();
		daeImage->AddComponent<dae::ImageComponent>();
		daeImage->AddComponent<dae::ImageRenderComponent>();
	

		daeImage->GetComponent<dae::ImageComponent>()->SetTexture("logo.tga");
		daeImage->GetComponent<dae::TransformComponent>()->SetLocalPosition(216.0f, 180.0f);

		scene.Add(daeImage);
	}


	// FPS
	{
		const SDL_Color fpsColor{ 255, 255, 0 };


		const auto fpsComponent = std::make_shared<dae::GameObject>();
		fpsComponent->AddComponent<dae::TextComponent>();
		fpsComponent->AddComponent<dae::TextRenderComponent>();
		fpsComponent->AddComponent<dae::FPSComponent>();


		fpsComponent->GetComponent<dae::TextComponent>()->SetFont(font);
		fpsComponent->GetComponent<dae::TextComponent>()->SetColor(fpsColor);
		fpsComponent->GetComponent<dae::TransformComponent>()->SetLocalPosition(0.0f, 10.0f);

		scene.Add(fpsComponent);
	}



	// Add the controller to the game
	auto& input = dae::InputManager::GetInstance();
	unsigned controller = input.AddController();


	constexpr float originalSpeed{ 50.0f };
	constexpr glm::vec2 playerMoveDirectionx{ 1,0 };
	constexpr glm::vec2 playerMoveDirectiony{ 0,1 };

	dae::MoveCommand* command{ nullptr };

	// Player 1 - Blue
	{
		const auto blueTank = std::make_shared<dae::GameObject>();
		blueTank->AddComponent<dae::ImageComponent>();
		blueTank->AddComponent<dae::ImageRenderComponent>();


		blueTank->GetComponent<dae::TransformComponent>()->SetLocalPosition(350.0f, 180.0f);
		blueTank->GetComponent<dae::ImageComponent>()->SetTexture("BlueTank.png");


		// ---- Controller Controls -----
		{
			command = input.AddControllerCommand<dae::MoveCommand>(
				std::make_unique<dae::MoveCommand>(blueTank.get()),
				dae::ControllerInput{ controller, dae::ControlerButton::DPAD_UP, dae::ButtonState::Pressed }
			);
			command->SetDirection({ playerMoveDirectiony });
			command->SetMoveSpeed(-originalSpeed);


			command = input.AddControllerCommand<dae::MoveCommand>(
				std::make_unique<dae::MoveCommand>(blueTank.get()),
				dae::ControllerInput{ controller, dae::ControlerButton::DPAD_DOWN,dae::ButtonState::Pressed }
			);
			command->SetDirection({ playerMoveDirectiony });
			command->SetMoveSpeed(originalSpeed);


			command = input.AddControllerCommand<dae::MoveCommand>(
				std::make_unique<dae::MoveCommand>(blueTank.get()),
				dae::ControllerInput{ controller, dae::ControlerButton::DPAD_RIGHT, dae::ButtonState::Pressed }
			);
			command->SetDirection({ playerMoveDirectionx });
			command->SetMoveSpeed(originalSpeed);


			command = input.AddControllerCommand<dae::MoveCommand>(
				std::make_unique<dae::MoveCommand>(blueTank.get()),
				dae::ControllerInput{ controller, dae::ControlerButton::DPAD_LEFT, dae::ButtonState::Pressed }
			);
			command->SetDirection({ playerMoveDirectionx });
			command->SetMoveSpeed(-originalSpeed);
		}

		scene.Add(blueTank);
	}

	// Player 2 - Red
	{
		auto redTank = std::make_shared<dae::GameObject>();
		redTank->AddComponent<dae::ImageComponent>();
		redTank->AddComponent<dae::ImageRenderComponent>();
		

		redTank->GetComponent<dae::TransformComponent>()->SetLocalPosition(350.0f, 180.0f);
		redTank->GetComponent<dae::ImageComponent>()->SetTexture("RedTank.png");

		// ---- Keyboard Controls -----
		{
			command = input.AddKeyboardCommand<dae::MoveCommand>(
				std::make_unique<dae::MoveCommand>(redTank.get()),
				dae::KeyboardInput{ SDL_SCANCODE_W, dae::ButtonState::Pressed }
			);
			command->SetDirection({ playerMoveDirectiony });
			command->SetMoveSpeed(-originalSpeed * 2);


			command = input.AddKeyboardCommand<dae::MoveCommand>(
				std::make_unique<dae::MoveCommand>(redTank.get()),
				dae::KeyboardInput{ SDL_SCANCODE_S, dae::ButtonState::Pressed }
			);
			command->SetDirection({ playerMoveDirectiony });
			command->SetMoveSpeed(originalSpeed * 2);


			command = input.AddKeyboardCommand<dae::MoveCommand>(
				std::make_unique<dae::MoveCommand>(redTank.get()),
				dae::KeyboardInput{ SDL_SCANCODE_A, dae::ButtonState::Pressed }
			);
			command->SetDirection({ playerMoveDirectionx });
			command->SetMoveSpeed(-originalSpeed * 2);

			command = input.AddKeyboardCommand<dae::MoveCommand>(
				std::make_unique<dae::MoveCommand>(redTank.get()),
				dae::KeyboardInput{ SDL_SCANCODE_D, dae::ButtonState::Pressed }
			);
			command->SetDirection({ playerMoveDirectionx });
			command->SetMoveSpeed(originalSpeed * 2);
		}


		scene.Add(redTank);	

	}



	// UI component
	auto UI = std::make_shared<dae::GameObject>();
	UI->AddComponent<dae::CacheComponent>();

	scene.Add(UI);
}

int main(int, char*[]) 
{
	m_Engine.Run(load);
    return 0;
}
