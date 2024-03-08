#include "CacheComponent.h"
#include "Renderer.h"
#include <algorithm>
#include <numeric>
#include <chrono>
#include <iostream>

#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl2.h>


using namespace std::chrono;

namespace dae
{
	CacheComponent::CacheComponent(GameObject* owner)
		:BaseComponent(owner)
		,m_ContainerSize{ 20'000'000 }
		,m_StepsInfo{ 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024 }
		,m_BenchmarkEx1{10}
		,m_BenchmarkEx2{10}
		,m_color1{ 255, 165, 0 }
		,m_color2{ 0, 165, 255 }
	{
		m_Window = Renderer::GetInstance().GetWindow();
	
		// Innitializing the ImGui
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui_ImplSDL2_InitForOpenGL(m_Window, SDL_GL_GetCurrentContext());
		ImGui_ImplOpenGL2_Init();
	}

	CacheComponent::~CacheComponent()
	{
		std::cout << "CacheComponent\n";


		ImGui_ImplOpenGL2_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
	}


	void CacheComponent::RenderUI()
	{
		// 1) Make an empty buffer
		ImGui_ImplOpenGL2_NewFrame();
		ImGui_ImplSDL2_NewFrame(m_Window);
		ImGui::NewFrame();


		RenderExcersize1();
		RenderExcersize2();


		//3) Swap the buffer so it is shown
		ImGui::Render();
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	}

	void CacheComponent::PlottingData(std::vector<float> data, ImColor color)
	{
		float maxVal = *std::max_element(begin(data), end(data));
		float minVal = *std::min_element(begin(data), end(data));


		// GRAPH
		ImGui::PlotConfig conf;
		conf.values.color = color;
		conf.values.ys = data.data();
		conf.values.xs = m_StepsInfo.data();
		conf.values.count = (int)m_StepsInfo.size() + 1;
		conf.scale.min = minVal;
		conf.scale.max = maxVal;
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.grid_y.show = true;
		conf.grid_x.show = false;
		conf.grid_y.size = maxVal / 10.0f;
		conf.frame_size = ImVec2(200, 100);
		conf.line_thickness = 2.f;

		ImGui::Plot("plot", conf);
	}


	// Exercise 1
	void CacheComponent::RenderExcersize1()
	{
		ImGui::Begin("Excersise 1");



		ImGui::InputInt("# samples", &m_BenchmarkEx1);
		if (m_BenchmarkEx1 < 1)
		{
			m_BenchmarkEx1 = 1;
		}

		if ( ImGui::Button("Trash the cache!") )
		{
			TrashTheCacheBenchmarkedTest(m_BenchmarkEx1);

		}

		if (m_IntAvarage.size() > 0)
		{
			PlottingData(m_IntAvarage, m_color1);
		}



		ImGui::End();
	}

	void CacheComponent::TrashTheCacheBenchmarkedTest(int benchmarkCount)
	{
		std::vector<int> intArray(m_ContainerSize, int{});
		const int maxSteps{ 11 };
		const int maxStepSize{ 1024 };
		std::vector<std::vector<long long>> ElapsedTimes(maxSteps, std::vector<long long>(benchmarkCount));



		for (int BenchmarkStep{ 0 }; BenchmarkStep < benchmarkCount; BenchmarkStep++)
		{
			int idx{ 0 };
			for (int stepsize = 1; stepsize <= maxStepSize; stepsize *= 2)
			{
				auto start = high_resolution_clock::now();

				// Do something
				for (int i{ 1 }; i < m_ContainerSize; i += stepsize)
				{
					intArray[i] *= 2;
				}

				auto end = high_resolution_clock::now();


				// Calculate and add the elapsed time
				auto elapsedTime = duration_cast<microseconds>(end - start).count();
				ElapsedTimes[idx++][BenchmarkStep] = elapsedTime;
			}
		}


		int stepSize{ 1 };
		std::vector<float> avarages;
		for (int i{ 0 }; i < maxSteps; i++)
		{
			std::sort(ElapsedTimes[i].begin(), ElapsedTimes[i].end());


			ElapsedTimes[i].erase(ElapsedTimes[i].begin());
			ElapsedTimes[i].pop_back();


			float avarage = std::accumulate(ElapsedTimes[i].begin(), ElapsedTimes[i].end(), 0.f) / ElapsedTimes[i].size();

			stepSize *= 2;
			avarages.push_back(avarage);
		}


		m_IntAvarage = avarages;
	}


	// Exercise 2
	void CacheComponent::RenderExcersize2()
	{
		ImGui::Begin("Excersise 2");



		ImGui::InputInt("# samples", &m_BenchmarkEx2);
		if (m_BenchmarkEx2 < 1)
		{
			m_BenchmarkEx2 = 1;
		}


		// Graph 1 - gameobject
		if (ImGui::Button("Trash the cache with gameobject!"))
		{
			GameObject3DTest(m_BenchmarkEx2);

		}

		if (m_ObjectAvarage.size() > 0)
		{
			PlottingData(m_ObjectAvarage, m_color1);
		}


		// Graph 2 - altered gameobject
		if (ImGui::Button("Trash the cache with altered gameobject!"))
		{
			GameObject3DAltTest(m_BenchmarkEx2);

		}

		if (m_ObjectAvarage.size() > 0)
		{
			PlottingData(m_AltObjectAvarage, m_color2);
		}


		// Graph 3	
		const ImU32 colors[2] = { m_color1, m_color2 };

		const float maxVal = std::max(*std::max_element(begin(m_ObjectAvarage), end(m_ObjectAvarage)), *std::max_element(begin(m_AltObjectAvarage), end(m_AltObjectAvarage)));
		const float minVal = std::min(*std::min_element(begin(m_ObjectAvarage), end(m_ObjectAvarage)), *std::min_element(begin(m_AltObjectAvarage), end(m_AltObjectAvarage)));

		const float* data[2] = { m_ObjectAvarage.data(), m_AltObjectAvarage.data() };


		ImGui::PlotConfig conf;
		conf.values.colors = colors;
		conf.values.ys_list = data;
		conf.values.xs = m_StepsInfo.data();
		conf.values.count = (int)m_StepsInfo.size() + 1;
		conf.values.ys_count = 2;
		conf.scale.min = minVal;
		conf.scale.max = maxVal;
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.grid_x.show = true;
		conf.grid_y.show = false;
		conf.grid_y.size = maxVal / 10.0f;
		conf.frame_size = ImVec2(200, 100);
		conf.line_thickness = 2.f;

		ImGui::Plot("Combined Graphs", conf);



		ImGui::End();
	}

	void CacheComponent::GameObject3DTest(int benchmarkCount)
	{
		std::vector<GameObject3D> objectVector{ (size_t)m_ContainerSize, GameObject3D{}};
		const int maxSteps{ 11 };
		const int maxStepSize{ 1024 };
		std::vector<std::vector<long long>> ElapsedTimes(maxSteps, std::vector<long long>(benchmarkCount));



		for (int BenchmarkStep{ 0 }; BenchmarkStep < benchmarkCount; BenchmarkStep++)
		{
			int idx{ 0 };
			for (int stepsize = 1; stepsize <= maxStepSize; stepsize *= 2)
			{
				auto start = high_resolution_clock::now();

				// Do something
				for (int i{ 1 }; i < m_ContainerSize; i += stepsize)
				{
					objectVector[i].ID *= 2;
				}

				auto end = high_resolution_clock::now();


				// Calculate and add the elapsed time
				auto elapsedTime = duration_cast<microseconds>(end - start).count();
				ElapsedTimes[idx++][BenchmarkStep] = elapsedTime;
			}
		}


		int stepSize{ 1 };
		std::vector<float> avarages;
		for (int i{ 0 }; i < maxSteps; i++)
		{
			std::sort(ElapsedTimes[i].begin(), ElapsedTimes[i].end());


			ElapsedTimes[i].erase(ElapsedTimes[i].begin());
			ElapsedTimes[i].pop_back();


			float avarage = std::accumulate(ElapsedTimes[i].begin(), ElapsedTimes[i].end(), 0.f) / ElapsedTimes[i].size();

			stepSize *= 2;
			avarages.push_back(avarage);
		}


		m_ObjectAvarage =  avarages;
	}

	void CacheComponent::GameObject3DAltTest(int benchmarkCount)
	{
		std::vector<GameObject3DAlt> objectVector{ (size_t)m_ContainerSize, GameObject3DAlt{} };
		const int maxSteps{ 11 };
		const int maxStepSize{ 1024 };
		std::vector<std::vector<long long>> ElapsedTimes(maxSteps, std::vector<long long>(benchmarkCount));



		for (int BenchmarkStep{ 0 }; BenchmarkStep < benchmarkCount; BenchmarkStep++)
		{
			int idx{ 0 };
			for (int stepsize = 1; stepsize <= maxStepSize; stepsize *= 2)
			{
				auto start = high_resolution_clock::now();

				// Do something
				for (int i{ 1 }; i < m_ContainerSize; i += stepsize)
				{
					objectVector[i].ID *= 2;
				}

				auto end = high_resolution_clock::now();


				// Calculate and add the elapsed time
				auto elapsedTime = duration_cast<microseconds>(end - start).count();
				ElapsedTimes[idx++][BenchmarkStep] = elapsedTime;
			}
		}


		int stepSize{ 1 };
		std::vector<float> avarages;
		for (int i{ 0 }; i < maxSteps; i++)
		{
			std::sort(ElapsedTimes[i].begin(), ElapsedTimes[i].end());


			ElapsedTimes[i].erase(ElapsedTimes[i].begin());
			ElapsedTimes[i].pop_back();


			float avarage = std::accumulate(ElapsedTimes[i].begin(), ElapsedTimes[i].end(), 0.f) / ElapsedTimes[i].size();

			stepSize *= 2;
			avarages.push_back(avarage);
		}


		m_AltObjectAvarage = avarages;
	}
}