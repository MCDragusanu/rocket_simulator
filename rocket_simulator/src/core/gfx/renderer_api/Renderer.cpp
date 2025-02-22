#pragma once
#include "Renderer.h"

Core::Gfx::RenderingSystem::Renderer* Core::Gfx::RenderingSystem::Renderer::pRendererAPI =nullptr;
Core::Gfx::RenderingSystem::Renderer* Core::Gfx::RenderingSystem::RenderCommand::pRendererAPI = nullptr;

void Core::Gfx::RenderingSystem::RenderCommand::setRendererAPI(Renderer* instance)
{
	pRendererAPI = instance;
}
