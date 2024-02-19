#include "BaseComponent.h"
#include "GameObject.h"
#include <iostream>


namespace dae
{
	BaseComponent::BaseComponent(GameObject* Owner)
		:m_pOwner{ Owner }
	{
	}

	BaseComponent::~BaseComponent()
	{
		std::cout << "HI\n";

		//delete m_pOwner;
		//m_pOwner = nullptr;
	}


	GameObject* BaseComponent::GetOwner() const
	{
		return m_pOwner;
	}

	void BaseComponent::Render() const
	{
	}

	void BaseComponent::Update()
	{
	}
}