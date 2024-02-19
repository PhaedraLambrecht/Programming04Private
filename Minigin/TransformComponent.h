#pragma once
#include "BaseComponent.h"
#include <glm/glm.hpp>


namespace dae
{
	class TransformComponent final : public BaseComponent
	{
	public:

		TransformComponent(GameObject* Owner);
		~TransformComponent() override;

		// Copy and move
		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) = delete;



		const glm::vec3& GetPosition() const;
		void SetPosition(float x, float y, float z); // todo: Does this need a z - and does it need to be v3?


	private:

		glm::vec3 m_Position;
	};
}

