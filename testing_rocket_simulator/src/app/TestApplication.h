#pragma once
#include "../../../rocket_simulator/src/engine/Application.h"
#include "../../../rocket_simulator/src/engine/AppState.h"
#include "../../../rocket_simulator/src/gfx/resources/Resource.h"

#include <vector>
#include <sstream>
#include <memory>

class TestApplication : public Core :: Application
{
public:

	TestApplication();

	// This method transitions the application to a new state
	void setState(std::unique_ptr<Core :: AppState> newState) override;

	void run()override;
	void start()override;
	bool is_running() override;
	bool initialize() override;
	bool load_resources()override;
	bool bind_resources()override;
	bool commit_resources()override;
	bool render()override;
	bool update()override;
	bool destroy()override;

private:
	bool is_active = true;
	std::unique_ptr<Core::AppState>						pCurrentState;
	std::stringstream									error_log, debug_log;
	GLFWwindow* pWindow = nullptr;
	Resources::ShaderProgram* pShaderProgram = nullptr;

	std::vector <Resources::Shader>					mShaderList;
	std::vector <Resources::VertexBuffer>				mVertexBufferList;
	std::vector <Resources::VertexArrayObject>		mVertexArrayObjectList;
};

