#pragma once
#include <cstdint>


namespace KarhuRayTracer
{
	class FrameBuffer
	{
	public:
		FrameBuffer();
		~FrameBuffer();

		void createFrameBuffer(uint32_t width, uint32_t height);
		void createRenderBuffer(uint32_t width, uint32_t height);

		void bind();
		void unbind();

		unsigned int getColorTExture() { return m_ColorTexture; }
	private:
		unsigned int m_FBO; /* FrameBuffer object. */
		unsigned int m_RBO; /* RenderBuffer object. */
		unsigned int m_ColorTexture;
	};
}