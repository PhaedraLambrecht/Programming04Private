#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <iostream>


namespace dae
{
	GameObject::GameObject()
	{
		m_pTransform = AddComponent<TransformComponent>();
	}

	GameObject::~GameObject()
	{
		std::cout << "\nGameObject\n";
	}


	void GameObject::Update()
	{
		// todo: easiest way to fix dead objects is walking trough the loop backwards
		for (const auto& component : m_pComponents)
		{
			component->Update();
		}
	}

	void GameObject::Render() const
	{
		for (const auto& component : m_pComponents)
		{
			component->Render();
		}
	}

	void GameObject::SetParent(std::shared_ptr<GameObject> parent, bool keepWorldPos)
	{
		if (!parent)
		{
			if (m_pTransform)
			{
				m_pTransform->SetLocalPosition(m_pTransform->GetWorldPosition().x, m_pTransform->GetWorldPosition().y);
			}
		}
		else
		{
			// Is the parent the same as this object?
			if (parent.get() == this)
			{
				throw std::invalid_argument("Parent cant be the same as the object it is set to");

			}
			
			// Is the new parent an alrady existing child to this object?
			for (int i{ 0 }; i < GetChildCount(); ++i)
			{
				if (GetChildAt(i) == parent.get()) 
				{
					throw std::invalid_argument("Parent cant be a previous child");
				}
			}


			// If neither of the above 2, set the transform
			if (keepWorldPos)
			{
				m_pTransform->SetLocalPosition(m_pTransform->GetLocalPosition().x - parent->GetTransform().GetWorldPosition().x,
											   m_pTransform->GetLocalPosition().y - parent->GetTransform().GetWorldPosition().y);
			}

			m_pTransform->SwitchDirtyFlag(true);
		}


		if (m_pParent)
		{
			m_pParent->RemoveChild( this );
		}

		m_pParent = parent;

		if (m_pParent)
		{
			m_pParent->AddChild( this );
		}
	}

	std::shared_ptr<GameObject> GameObject::GetParent() const
	{
		return m_pParent;
	}

	int GameObject::GetChildCount() const
	{
		return int(m_pChildren.size());
	}

	GameObject* GameObject::GetChildAt(int index) const
	{
		return m_pChildren[index];
	}

	std::vector<GameObject*> GameObject::GetChildren() const
	{
		return m_pChildren;
	}

	TransformComponent& GameObject::GetTransform() const
	{
		return *m_pTransform;
	}

	void GameObject::AddChild(GameObject* pChild)
	{
		const auto it = std::find(m_pChildren.begin(), m_pChildren.end(), pChild);

		if (it == m_pChildren.end())
		{
			m_pChildren.push_back( pChild);
		}
	}

	void GameObject::RemoveChild(GameObject* pChild)
	{
		m_pChildren.erase(std::remove(std::begin(m_pChildren), std::end(m_pChildren), pChild));
	}

}