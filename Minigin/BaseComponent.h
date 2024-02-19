#pragma once


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

		// todo: Do you need to be smart or is raw oke?
		GameObject* m_pOwner;
	};
}


