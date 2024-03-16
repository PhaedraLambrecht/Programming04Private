#pragma once

namespace dae
{
	class GameObject;

	class Command
	{
	public:

		explicit Command(GameObject* pActor);
		virtual ~Command() = default;

		Command(const Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) = delete;




		virtual void Execute() = 0;
		GameObject* GetActor() const;


	private:

		GameObject* m_pActor;

	};

}
