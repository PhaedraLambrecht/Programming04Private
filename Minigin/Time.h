#pragma once
#include "Singleton.h"
#include <chrono>


namespace dae
{
	class Time final: public Singleton<Time>
	{
	public:

		Time();
		virtual ~Time() = default;

		// Copy and move
		Time(const Time& other) = delete;
		Time(Time&& other) = delete;
		Time& operator=(const Time& other) = delete;	
		Time& operator=(Time&& other) = delete;



		void Update();
		float GetDeltaTime() const;
		float GetFixedTimeStep() const;
		int GetMSPerFrame() const;
		std::chrono::time_point<std::chrono::steady_clock> GetPreviousTime() const;


	private:

		float m_DeltaTime;
		const int m_FrameRateCap;
		const float m_FixedTimeStep;
		int m_MSPerFrame;
		std::chrono::time_point<std::chrono::steady_clock> m_PreviousTime;

	};
}
