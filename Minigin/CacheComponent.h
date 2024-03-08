#pragma once
#include "BaseComponent.h"
#include "imgui_plot.h"
#include <vector>
#include <map>
#include <SDL.h>


namespace dae
{

	class CacheComponent final : public BaseComponent
	{
	public:

		CacheComponent(GameObject* owner);
		~CacheComponent() override;

		CacheComponent(const CacheComponent& other) = delete;
		CacheComponent(CacheComponent&& other) = delete;
		CacheComponent& operator=(const CacheComponent& other) = delete;
		CacheComponent& operator=(CacheComponent&& other) = delete;




		void RenderUI() override;


	private:

		SDL_Window* m_Window;

		std::vector<float> m_StepsInfo;
		const int m_ContainerSize;
		ImColor m_color1;
		ImColor m_color2;

		// Helper function
		void PlottingData(std::vector<float> data, ImColor color);



		// Exercise 1
		int m_BenchmarkEx1;
		std::vector<float> m_IntAvarage = std::vector<float>(11);
	
		// Helper functions exercise 1
		void RenderExcersize1();
		void TrashTheCacheBenchmarkedTest(int benchmarkCount);



		// Exercise 2
		struct Transform
		{
			float matrix[16] =
			{
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1
			};
		};
		class GameObject3D
		{
		public:
			Transform transform;
			int ID;
		};
		class GameObject3DAlt
		{
		public:
			Transform* transform;
			int ID;
		};

		int m_BenchmarkEx2;
		std::vector<float> m_ObjectAvarage = std::vector<float>(11);
		std::vector<float> m_AltObjectAvarage = std::vector<float>(11);

		// Helper functions exercise 2
		void RenderExcersize2();
		void GameObject3DTest(int benchmarkCount);
		void GameObject3DAltTest(int benchmarkCount);

	
	};

}
