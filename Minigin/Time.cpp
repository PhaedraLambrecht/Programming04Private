#include "Time.h"


namespace dae
{
	Time::Time()
		:m_DeltaTime{}
		, m_FrameRateCap{ 60 }
		, m_FixedTimeStep{ 0.1f } // so one can actually read the fps atm, normal value is 0.01f
		, m_PreviousTime{ std::chrono::high_resolution_clock::now() }
	{
		m_MSPerFrame = 1000 / m_FrameRateCap;
	}


	void Time::Update()
	{
		const auto currentTime = std::chrono::high_resolution_clock::now();
		m_DeltaTime = std::chrono::duration<float>(currentTime - m_PreviousTime).count();


		m_PreviousTime = currentTime;
	}

	float Time::GetDeltaTime() const
	{
		return m_DeltaTime;
	}

	float Time::GetFixedTimeStep() const
	{
		return m_FixedTimeStep;
	}

	int Time::GetMSPerFrame() const
	{
		return m_MSPerFrame;
	}

	std::chrono::time_point<std::chrono::steady_clock> Time::GetPreviousTime() const
	{
		return m_PreviousTime;
	}
}