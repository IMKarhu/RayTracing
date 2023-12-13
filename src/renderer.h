#pragma once
#include "gameObject.h"
#include "frameBuffer.h"
#include "texture.h"
//#include "skyboxData.h"
#include <vector>
#include <memory>

namespace KarhuRayTracer
{
	class Window;
	class Shader;
	class Camera;
	class Renderer
	{
	public:
		Renderer(Window& window);
		~Renderer();

		void render(std::vector<Shader>& m_Shaders, Camera& m_Camera, Object m_Object, float dt);
		void update(float dt);
		void rescaleFrameBuffer(float width, float height);

		//unsigned int getFrameBuffer() { return fbotex; }
	private:
		Window& m_Window;
		
		//Texture m_SkyBoxTexture{};
		//FrameBuffer m_FrameBuffer{};
		unsigned int m_VAO;
		unsigned int m_VBO; /* Vertex buffer object. */
		unsigned int m_EBO; /* Element buffer object. */
		unsigned int ssbo;
		unsigned int texture;
	};
}