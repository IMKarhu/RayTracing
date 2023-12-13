#include "frameBuffer.h"
#include "glad.h"

namespace KarhuRaytracer
{

}

KarhuRayTracer::FrameBuffer::FrameBuffer()
{
}

KarhuRayTracer::FrameBuffer::~FrameBuffer()
{
}

void KarhuRayTracer::FrameBuffer::createFrameBuffer(uint32_t width, uint32_t height)
{
	glGenFramebuffers(1, &m_FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

	glGenTextures(1, &m_ColorTexture);
	glBindTexture(GL_TEXTURE_2D, m_ColorTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorTexture, 0);
}

void KarhuRayTracer::FrameBuffer::createRenderBuffer(uint32_t width, uint32_t height)
{
	glGenRenderbuffers(1, &m_RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_RBO);
}

void KarhuRayTracer::FrameBuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
}

void KarhuRayTracer::FrameBuffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
