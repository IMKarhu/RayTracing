#pragma once


namespace KarhuRayTracer
{
	class FrameBuffer
	{
	public:
		FrameBuffer();
		~FrameBuffer();

		void bind();
		void unbind();
	private:
	};
}