#pragma once
#include <memory>


namespace dae
{
	class GameObject;

	class BaseComponent
	{
	public:

		virtual ~BaseComponent();

		// Copy and move
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;



		virtual void Render() const;
		virtual void Update();


	protected:

		BaseComponent(GameObject* Owner);
		GameObject* GetOwner() const;


	private:

		// todo: Can be a smart pointer --> Preferably a shared_ptr
		GameObject* m_pOwner;
	};
}


