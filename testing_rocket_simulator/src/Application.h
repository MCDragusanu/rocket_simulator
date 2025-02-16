#pragma once

//#include "../../rocket_simulator/src/core/window/MainWindow.h"
#include "../../rocket_simulator/src/core/window/MainWindow.h"
#include "../../rocket_simulator/src/core/events/EventHandler.h"
#include "../../rocket_simulator/src/core/gfx/Buffer.h"
#include "../../rocket_simulator/src/core/gfx/shaders_api/Shader.h"
#include "../../rocket_simulator/src/core/gfx/shaders_api/ShaderPipeline.h"
#include "../../rocket_simulator/src/core/gfx/VertexArray.h"



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
	std::shared_ptr<Core::gfx::VertexArray> pVertexArray ;
	std::shared_ptr<Core::gfx::IndexBuffer> pIndexBuffer ;
	std::shared_ptr < Core::gfx::VertexBuffer> pVertexBuffer;

	Core::Window::MainWindow* mMainWindow = { nullptr };

	Core::gfx::shaders::ShaderPipeline* pShaderPipeline = { nullptr };
	Core::gfx::shaders::VertexShader* pVertexShader = { nullptr };
	Core::gfx::shaders::FragmentShader* pFragmentShader = { nullptr };
	bool mIsRunning = { false };
};
