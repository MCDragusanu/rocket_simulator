#include "OpenGLDrawIndexed.h"
#include "../../../../../include/glad/glad.h"
#include "../../../../../include/glfw/glfw3.h"
OpenGL::Gfx::RenderSystem::Commands::OpenGLDrawIndexed::OpenGLDrawIndexed(const std::shared_ptr<Core::Gfx::MeshSystem::VertexArray>& vertexArray):vertexArray(vertexArray)
{
}

Core::Gfx::RenderingSystem::CommandType OpenGL::Gfx::RenderSystem::Commands::OpenGLDrawIndexed::getType()
{
	return Core::Gfx::RenderingSystem::CommandType::DrawIndexed;
}

void OpenGL::Gfx::RenderSystem::Commands::OpenGLDrawIndexed::execute()
{
	glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
}
