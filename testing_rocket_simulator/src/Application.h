#pragma once

//#include "../../rocket_simulator/src/core/window/MainWindow.h"
#include "../../rocket_simulator/src/core/window/MainWindow.h"
#include "../../rocket_simulator/src/core/events/EventHandler.h"
#include "../../rocket_simulator/src/core/Gfx/Buffer.h"
#include "../../rocket_simulator/src/core/Gfx/shaders_api/Shader.h"
#include "../../rocket_simulator/src/core/Gfx/shaders_api/ShaderPipeline.h"
#include "../../rocket_simulator/src/core/Gfx/VertexArray.h"



class Application : private Core::Events::EventCallback {
public:
	Application() {};
	~Application() {}
	void init();
	void update();
	void release();
	bool isRunning();
protected:
	void prepareShutDown();
private:
	void on_window_event(const std::unique_ptr<Core::Events::Event>& event) override;
	void on_keyboard_event(const std::unique_ptr<Core::Events::Event>& event) override;
	void on_mouse_event(const std::unique_ptr<Core::Events::Event>& event) override;
	std::shared_ptr<Core::Gfx::VertexArray> pVertexArray ;
	std::shared_ptr<Core::Gfx::IndexBuffer> pIndexBuffer ;
	std::shared_ptr < Core::Gfx::VertexBuffer> pVertexBuffer;

	Core::Window::MainWindow* mMainWindow = { nullptr };

	Core::Gfx::ShaderSystem::ShaderPipeline* pShaderPipeline = { nullptr };
	Core::Gfx::ShaderSystem::VertexShader* pVertexShader = { nullptr };
	Core::Gfx::ShaderSystem::FragmentShader* pFragmentShader = { nullptr };
	bool mIsRunning = { false };
};
