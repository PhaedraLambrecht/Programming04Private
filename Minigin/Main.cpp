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

// FPS counter
#include "GameObject.h"
#include "ImageComponent.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "ImageRenderComponent.h"
#include "TextRenderComponent.h"
#include "FPSComponent.h"
#include "RotatorComponent.h"

// Input 
#include "InputManager.h"
#include "Controller.h"
#include "MoveCommand.h"

// Event queue
#include "EventManager.h"
#include "HealthComponent.h"
#include "LivesComponent.h"
#include "AddPointsComponnent.h"
#include "AddPointsCommand.h"
#include "ScoreComponent.h"
#include "DamageCommand.h"

#include "PlayManualComponent.h"
#include <memory>

#include <iostream>
dae::Minigin m_Engine("../Data/");


void LoadLevel(dae::Scene& scene, std::shared_ptr<dae::Font> font)
{
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
		std::string text = "Programming 4 - Tron";


		const auto title = std::make_shared<dae::GameObject>();
		title->AddComponent<dae::TextComponent>();
		title->AddComponent<dae::TextRenderComponent>();

		title->GetComponent<dae::TextComponent>()->SetFont(font);
		title->GetComponent<dae::TextComponent>()->SetColor(tittleColor);
		title->GetComponent<dae::TextComponent>()->SetText(text);
		title->GetComponent<dae::TransformComponent>()->SetLocalPosition(170.0f, 30.0f);


		scene.Add(title);
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
}



void LoadPlayerStats(dae::Scene& scene, const unsigned int playerIndex, const glm::vec2 position)
{
	const SDL_Color color{ 0, 255, 0 };
	const auto font{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 25) };


	// Player lives
	{
		const auto livesDisplay = std::make_shared<dae::GameObject>();
		livesDisplay->AddComponent<dae::TextComponent>();
		livesDisplay->AddComponent<dae::TextRenderComponent>();
		livesDisplay->GetComponent<dae::TextComponent>()->SetFont(font);
		livesDisplay->GetComponent<dae::TextComponent>()->SetColor(color);
		livesDisplay->AddComponent<dae::LivesComponent>();


		livesDisplay->GetComponent<dae::TransformComponent>()->SetLocalPosition(position.x, position.y);
		livesDisplay->GetComponent<dae::LivesComponent>()->SetPlayerIndex(playerIndex);

		scene.Add(livesDisplay);
	}

	//PLayer score
	{
		const auto scoreDisplay = std::make_shared<dae::GameObject>();
		scoreDisplay->AddComponent<dae::TextComponent>();
		scoreDisplay->AddComponent<dae::TextRenderComponent>();
		scoreDisplay->GetComponent<dae::TextComponent>()->SetFont(font);
		scoreDisplay->GetComponent<dae::TextComponent>()->SetColor(color);
		scoreDisplay->AddComponent<dae::ScoreComponent>();


		scoreDisplay->GetComponent<dae::TransformComponent>()->SetLocalPosition(position.x, position.y + 40.0f);
		scoreDisplay->GetComponent<dae::ScoreComponent>()->SetPlayerIndex(playerIndex);

		scene.Add(scoreDisplay);
	}

}

void LoadPlayer(dae::Scene& scene, dae::InputManager& input, const unsigned int playerIndex, const bool IsControllerUsed, const std::string texture, const glm::vec2 position)
{
	// Setting up some needed variables
	dae::MoveCommand* command{ nullptr };
	constexpr float originalSpeed{ 100.0f };
	constexpr glm::vec2 playerMoveDirectionx{ 1,0 };
	constexpr glm::vec2 playerMoveDirectiony{ 0,1 };




	const auto playerObject = std::make_shared<dae::GameObject>();
	playerObject->AddComponent<dae::ImageComponent>();
	playerObject->AddComponent<dae::ImageRenderComponent>();
	playerObject->AddComponent<dae::HealthComponent>();
	playerObject->AddComponent<dae::AddPointsComponnent>();


	playerObject->GetComponent<dae::TransformComponent>()->SetLocalPosition(position.x + 30.0f, position.y);
	playerObject->GetComponent<dae::ImageComponent>()->SetTexture(texture);
	playerObject->GetComponent<dae::AddPointsComponnent>()->SetPlayerIndex(playerIndex);
	playerObject->GetComponent<dae::HealthComponent>()->SetPlayerIndex(playerIndex);

	scene.Add(playerObject);



	
	if (IsControllerUsed)
	{
		unsigned controller = input.AddController();


		// Movement
		command = input.AddControllerCommand<dae::MoveCommand>(
			std::make_unique<dae::MoveCommand>(playerObject.get(), playerMoveDirectiony, -originalSpeed),
			dae::ControllerInput{ controller, dae::ControlerButton::DPAD_UP, dae::ButtonState::Pressed }
		);

		command = input.AddControllerCommand<dae::MoveCommand>(
			std::make_unique<dae::MoveCommand>(playerObject.get(), playerMoveDirectiony, originalSpeed),
			dae::ControllerInput{ controller, dae::ControlerButton::DPAD_DOWN,dae::ButtonState::Pressed }
		);

		command = input.AddControllerCommand<dae::MoveCommand>(
			std::make_unique<dae::MoveCommand>(playerObject.get(), playerMoveDirectionx, -originalSpeed),
			dae::ControllerInput{ controller, dae::ControlerButton::DPAD_LEFT, dae::ButtonState::Pressed }
		);

		command = input.AddControllerCommand<dae::MoveCommand>(
			std::make_unique<dae::MoveCommand>(playerObject.get(), playerMoveDirectionx, originalSpeed),
			dae::ControllerInput{ controller, dae::ControlerButton::DPAD_RIGHT, dae::ButtonState::Pressed }
		);


		// points added
		input.AddControllerCommand<dae::AddPointsCommand>(
			std::make_unique<dae::AddPointsCommand>(playerObject.get()),
			dae::ControllerInput{ playerIndex, dae::ControlerButton::B, dae::ButtonState::Up });

		// Lifes taken
		input.AddControllerCommand<dae::DamageCommand>(
			std::make_unique<dae::DamageCommand>(playerObject.get(), 1.0f),
			dae::ControllerInput{ playerIndex, dae::ControlerButton::A, dae::ButtonState::Up });
	}
	else
	{
		// Movement
		command = input.AddKeyboardCommand<dae::MoveCommand>(
			std::make_unique<dae::MoveCommand>(playerObject.get(), playerMoveDirectiony, -originalSpeed),
			dae::KeyboardInput{ SDL_SCANCODE_W, dae::ButtonState::Pressed }
		);

		command = input.AddKeyboardCommand<dae::MoveCommand>(
			std::make_unique<dae::MoveCommand>(playerObject.get(), playerMoveDirectiony, originalSpeed),
			dae::KeyboardInput{ SDL_SCANCODE_S, dae::ButtonState::Pressed }
		);


		command = input.AddKeyboardCommand<dae::MoveCommand>(
			std::make_unique<dae::MoveCommand>(playerObject.get(), playerMoveDirectionx, -originalSpeed),
			dae::KeyboardInput{ SDL_SCANCODE_A, dae::ButtonState::Pressed }
		);

		command = input.AddKeyboardCommand<dae::MoveCommand>(
			std::make_unique<dae::MoveCommand>(playerObject.get(), playerMoveDirectionx, originalSpeed),
			dae::KeyboardInput{ SDL_SCANCODE_D, dae::ButtonState::Pressed }
		);




		// points added
		input.AddKeyboardCommand<dae::AddPointsCommand>(
			std::make_unique<dae::AddPointsCommand>(playerObject.get()),
			dae::KeyboardInput{ SDL_SCANCODE_Q , dae::ButtonState::Up });

		// Lifes taken
		input.AddKeyboardCommand<dae::DamageCommand>(
			std::make_unique<dae::DamageCommand>(playerObject.get(), 1.0f),
			dae::KeyboardInput{ SDL_SCANCODE_E, dae::ButtonState::Up });
	}




	// ---- Printing player stats -----
	LoadPlayerStats(scene, playerIndex, { position.x - 190.0f, position.y });

}



void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	const auto font{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 25) };
	auto& input = dae::InputManager::GetInstance();


	LoadLevel(scene, font);


	// Load the players (and their stats)
	LoadPlayer(scene, input, 0, true, "BlueTank.png", { 200.0f, 200.0f }); // PLayer 0 - Blue
	LoadPlayer(scene, input, 1, false, "RedTank.png", { 200.0f, 300.0f }); // PLayer 1 - Red



	// ---- Play manual -----
	const auto playManual = std::make_shared<dae::GameObject>();
	playManual->AddComponent<dae::PlayManualComponent>();


	// Keyboard
	{
		playManual->GetComponent<dae::PlayManualComponent>()->AddControl("WASD");
		playManual->GetComponent<dae::PlayManualComponent>()->AddDescription("Move");

		playManual->GetComponent<dae::PlayManualComponent>()->AddControl("E");
		playManual->GetComponent<dae::PlayManualComponent>()->AddDescription("Lose a life");
		playManual->GetComponent<dae::PlayManualComponent>()->AddControl("Q");
		playManual->GetComponent<dae::PlayManualComponent>()->AddDescription("Gain 100 points\n");

	}
	// Controller
	{
		playManual->GetComponent<dae::PlayManualComponent>()->AddControl("DPAD");
		playManual->GetComponent<dae::PlayManualComponent>()->AddDescription("Move");

		playManual->GetComponent<dae::PlayManualComponent>()->AddControl("A_BUTTON");
		playManual->GetComponent<dae::PlayManualComponent>()->AddDescription("Lose a life");
		playManual->GetComponent<dae::PlayManualComponent>()->AddControl("B_BUTTON");
		playManual->GetComponent<dae::PlayManualComponent>()->AddDescription("Gain 100 points");
	}

	scene.Add(playManual);
}

int main(int, char*[]) 
{
	m_Engine.Run(load);
    return 0;
}
