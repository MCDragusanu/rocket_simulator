#include "OpenGLRenderer.h"
#include "../../../../include/glad/glad.h"
#include "../../../../include/glfw/glfw3.h"

void OpenGL::Gfx::RenderingSystem::OpenGLRenderer::setClearColor(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
}

void OpenGL::Gfx::RenderingSystem::OpenGLRenderer::clear()
{
	glClear(GL_COLOR_BUFFER_BIT || GL_DEPTH_BUFFER_BIT);
}

void OpenGL::Gfx::RenderingSystem::OpenGLRenderer::setThread(std::thread& renderingThread)
{
}

void OpenGL::Gfx::RenderingSystem::OpenGLRenderer::addCommand(Core::Gfx::RenderingSystem::RenderCommand* command)
{
	mCommandQueue.push(command);
}

void OpenGL::Gfx::RenderingSystem::OpenGLRenderer::executeCommands()
{
	while (!mCommandQueue.empty()) {
		Core::Gfx::RenderingSystem::RenderCommand* command;
		if (mCommandQueue.try_pop(command)) {
			assert(command != nullptr);
			if (command != nullptr) {
				command->execute();
			}
		}

	}
}

void OpenGL::Gfx::RenderingSystem::OpenGLRenderer::drawIndexed(const std::shared_ptr<Core::Gfx::VertexArray>& vertexArray)
{
	
	glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
}


OpenGL::Gfx::RenderingSystem::OpenGLRenderer::OpenGLRenderer(std::shared_ptr<OpenGLContext>& context):mContext(context)
{
	Core::Gfx::RenderingSystem::Renderer::pRendererAPI = this;
	Core::Gfx::RenderingSystem::RenderCommand::setRendererAPI(this);
}

void OpenGL::Gfx::RenderingSystem::OpenGLRenderer::beginScene(const Core::Gfx::SceneSystem::Scene& scene)
{
	
	scene.bindScene();
	auto commands = getCommands(scene);
	for (const auto& command : commands) {
		mCommandQueue.push(command);
	}

}

void OpenGL::Gfx::RenderingSystem::OpenGLRenderer::endScene()
{
}

void OpenGL::Gfx::RenderingSystem::OpenGLRenderer::submit()
{
	
	executeCommands();
}
