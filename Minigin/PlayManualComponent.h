#pragma once
#include "BaseComponent.h"
#include <iostream>
#include <vector>

namespace dae
{
	class PlayManualComponent final : public BaseComponent
	{
	public:

		PlayManualComponent(GameObject* owner);
		~PlayManualComponent() override;

		PlayManualComponent(const PlayManualComponent& other) = delete;
		PlayManualComponent(PlayManualComponent&& other) = delete;
		PlayManualComponent& operator=(const PlayManualComponent& other) = delete;
		PlayManualComponent& operator=(PlayManualComponent&& other) = delete;




		void RenderUI() override;
		// todo: make this accept a vector of these to make life easier
		void AddControl(std::string controls);
		void AddDescription(std::string description);


	private:

		void SetText();

		bool m_IstextUpdated;
		std::string m_Text;

		std::vector<std::string> m_Controls;
		std::vector<std::string> m_descriptions;

	};
}


