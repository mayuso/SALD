#pragma once
#include "saldpch.h"

#include "Sald/Renderer/RendererAPI.h"
#include "Sald/Renderer/GraphicsContext.h"

namespace Sald {

	class RenderCommand
	{
	public:
		static void Init()
		{
			s_RendererAPI->Init();
			//s_GraphicsContext->Init();
		}

		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

		static void SetClearColor(float r, float g, float b, float a)
		{
			s_RendererAPI->SetClearColor(r, g, b, a);
		}

		static void Clear()
		{
			s_RendererAPI->Clear();
		}

		
		
	private:
		static std::unique_ptr<RendererAPI> s_RendererAPI;
	};

}