#pragma once
#include "TransformComponent.h"
#include <memory>
#include <vector>
#include <algorithm>


namespace dae
{
	class BaseComponent;
	class TransformComponent;


	class GameObject final
	{
	public:

		GameObject();
		~GameObject();

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;



		void Update();
		void Render() const;

		template <typename T> T* AddComponent();
		template <typename T> T* GetComponent() const;
		template <typename T> void RemoveComponent();
	
		
	private:

		std::vector<std::unique_ptr<BaseComponent>> m_pComponents;
		std::unique_ptr<TransformComponent> m_pTransform;

	};




	template<typename T>
	inline T* GameObject::AddComponent()
	{
		// Ensure that the template argument is derived from BaseComponent
		static_assert(std::is_base_of<BaseComponent, T>(), "Provided template argument is not a component");


		auto newComponent = std::make_unique<T>(this); // Create a new component of the specified type
		T* rawPointer = newComponent.get();	// Get a raw pointer to the newly created component


		m_pComponents.push_back(std::move(newComponent));
		return rawPointer;
	}

	template<typename T>
	inline T* GameObject::GetComponent() const
	{
		static_assert(std::is_base_of<BaseComponent, T>::value, "Provided template argument is not a component");

		// Search for a component of the specified type in the GameObject
		for (const auto& component : m_pComponents)
		{
			// Check if the component is of the specified type
			T* foundComponent = dynamic_cast<T*>(component.get());

			if (foundComponent)
			{
				return foundComponent;
			}
		}


		return nullptr;
	}

	template<typename T>
	inline void GameObject::RemoveComponent()
	{
		static_assert(std::is_base_of<BaseComponent, T>::value, "Provided template argument is not a component");


		// Search for a component of the specified type in the GameObject
		for (const auto& component : m_pComponents)
		{
			// Check if the component is of the specified type
			T* foundComponent = dynamic_cast<T*>(component.get());

			if (foundComponent != nullptr)
			{
				foundComponent = nullptr;
			}
		}

	}

}
