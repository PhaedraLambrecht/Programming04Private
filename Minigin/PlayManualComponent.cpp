#include "PlayManualComponent.h"
#include "imgui.h"

dae::PlayManualComponent::PlayManualComponent(GameObject* owner)
	:BaseComponent(owner)
	, m_Text{}
	, m_Controls{}
	, m_descriptions{}
	,m_IstextUpdated{true}
{

}

dae::PlayManualComponent::~PlayManualComponent()
{
	std::cout << "PlayManualComponent\n";
}

void dae::PlayManualComponent::RenderUI()
{
	ImGui::Begin("Play Manual");

	if(!m_IstextUpdated)
		SetText();

	ImGui::Text(m_Text.c_str());

	ImGui::End();
}

void dae::PlayManualComponent::AddControl(std::string controls)
{
	m_Controls.push_back(controls);
	m_IstextUpdated = false;
}

void dae::PlayManualComponent::AddDescription(std::string description)
{
	m_descriptions.push_back(description);
	m_IstextUpdated = false;
}

void dae::PlayManualComponent::SetText()
{
	for (int i{ 0 }; i < int(m_Controls.size()); ++i)
	{
		m_Text +=  m_Controls[i] + ": " + m_descriptions[i] + '\n';
	}
	m_IstextUpdated = true;
}
