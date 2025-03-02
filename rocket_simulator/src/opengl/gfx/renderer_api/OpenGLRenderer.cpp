#include "OpenGLRenderer.h"
#include "../../../../include/glad/glad.h"
#include "../../../../include/glfw/glfw3.h"
#include <mutex>
void OpenGL::Gfx::RenderingSystem::OpenGLRenderer::setClearColor(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
}

void OpenGL::Gfx::RenderingSystem::OpenGLRenderer::clear()
{
	glClear(GL_COLOR_BUFFER_BIT || GL_DEPTH_BUFFER_BIT);
}


void OpenGL::Gfx::RenderingSystem::OpenGLRenderer::endDraw()
{

}

void OpenGL::Gfx::RenderingSystem::OpenGLRenderer::addCommand(const Core::Gfx::RenderingSystem::RenderCommand* command)
{
	addCommand(const_cast<Core::Gfx::RenderingSystem::RenderCommand*>(command));
}

void OpenGL::Gfx::RenderingSystem::OpenGLRenderer::addCommand(Core::Gfx::RenderingSystem::RenderCommand* command)
{
	mBackBuffer.push(command);
}

OpenGL::Gfx::RenderingSystem::OpenGLRenderer::OpenGLRenderer(std::shared_ptr<OpenGLContext>& context):mContext(context)
{
	Core::Gfx::RenderingSystem::Renderer::pRendererAPI = this;
	Core::Gfx::RenderingSystem::RenderCommand::setRendererAPI(this);
}

void OpenGL::Gfx::RenderingSystem::OpenGLRenderer::beginDraw()
{
	{
		std::lock_guard<std::mutex> lock(queueMutex);
		std::swap(mFrontBuffer, mBackBuffer);
	
	}
	while (!mFrontBuffer.empty()) {
		auto command = mFrontBuffer.front();
		mFrontBuffer.pop();
		if (command) command->execute(); // Execute rendering command
	}
	
	
}


