#include "TestApplication.h"
#include "../../../rocket_simulator/src/engine/AppState.h"
#include "../states/init/InitState.h"

TestApplication::TestApplication()
{
    InitState* new_state = new InitState(*this);
    pCurrentState = std::unique_ptr <Core::AppState>(new_state);
    
}

void TestApplication::setState(std::unique_ptr<Core::AppState> newState)
{
    this->pCurrentState = std::move(newState);
   
}
void TestApplication::run()
{
   
        if (pCurrentState.get() != nullptr /* && !glfwWindowShouldClose(pWindow)*/) {
            pCurrentState.get()->handle(); // Handle the current state logic
        }
        else {
            is_active = false;
        }

      
    
}

void TestApplication::start()
{
    is_active = true;
    pCurrentState->handle();
    
}

bool TestApplication::is_running() {
    return !glfwWindowShouldClose(pWindow);
}
bool TestApplication::initialize()
{
    // Initialize GLFW
    int glfw_status = glfwInit();
    if (!glfw_status) {
        this->error_log << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    pWindow = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (pWindow == NULL) {
        this->error_log << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(pWindow);
    glfwSwapInterval(1);  // Enable vsync (optional)


    int glad_status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    // Initialize GLAD

    if (!glad_status) {
        this->error_log << "Failed to initialize GLAD" << std::endl;
        return false;
    }



    const auto framebuffer_size_callback = [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    };


    auto callback_status = glfwSetFramebufferSizeCallback(pWindow, framebuffer_size_callback);
    if (!callback_status) {
        this->error_log << "Failed to set Frame Buffer Size Callback << " << "\n";
    }

    glViewport(0, 0, 800, 600);
    pShaderProgram = new Resources::ShaderProgram();
    return true;
}

bool TestApplication::load_resources()
{
    try {
        const char pixel_shader_path[] = "resources\\shaders\\pixel_shader.txt";
        const char vertex_shader_path[] = "resources\\shaders\\vertex_shader.txt";


        this->mShaderList.emplace_back(pixel_shader_path, "PixelShader", Resources::ResourceType::SHADER_FRAGMENT, true);
        this->mShaderList.emplace_back(vertex_shader_path, "VertexShader", Resources::ResourceType::SHADER_VERTEX, true);

        auto buffer_content = std::make_unique<float[]>(9);
        size_t i = -1;
        buffer_content[++i] = -0.5f; // First vertex (x, y, z)
        buffer_content[++i] = -0.5f;
        buffer_content[++i] = 0.0f;

        buffer_content[++i] = 0.5f; // Second vertex (x, y, z)
        buffer_content[++i] = -0.5f;
        buffer_content[++i] = 0.0f;

        buffer_content[++i] = 0.0f; // Third vertex (x, y, z)
        buffer_content[++i] = 0.5f;
        buffer_content[++i] = 0.0f;

        this->mVertexBufferList.emplace_back(std::move(buffer_content), 3, 3 * sizeof(float));
        this->mVertexArrayObjectList.emplace_back(0, 3, 3 * sizeof(float));
        return true;
    }
    catch (const std::exception& e) {
        this->error_log << "ERROR     : Load Resources Stage Failed!\n";
        this->error_log << "Reason    :" << e.what();
        return false;
    }
}

bool TestApplication::bind_resources()
{
    try {
        for (auto& vbo : this->mVertexBufferList) {
            GLuint vbo_uid;
            glGenBuffers(1, &vbo_uid);  // Generate buffer
            glBindBuffer(GL_ARRAY_BUFFER, vbo_uid);  // Bind buffer
            vbo.set_resouce_id(vbo_uid);
        }

        for (auto iterator = this->mVertexArrayObjectList.begin(); iterator < mVertexArrayObjectList.end(); ++iterator) {
            GLuint vao_uid;
            glGenVertexArrays(1, &vao_uid);  // Generate VAO
            glBindVertexArray(vao_uid);  // Bind VAO
            iterator->set_resouce_id(vao_uid);
            glVertexAttribPointer(iterator - mVertexArrayObjectList.begin(), iterator->get_vertex_count(), iterator->get_vertex_type(), GL_FALSE, iterator->get_vertex_stride(), (void*)(iterator->get_vertex_offset()));  // Define vertex format
            glEnableVertexAttribArray(iterator - mVertexArrayObjectList.begin());  // Enable vertex attribute for position
        }

        for (auto& shader : mShaderList) {
            bool status = pShaderProgram->compile_shader(shader);
            if (!status) return false;
        }


        pShaderProgram->run_program();
        return true;
    }
    catch (const std::exception& e) {
        this->error_log << "ERROR     : Bind Resources Stage Failed!\n";
        this->error_log << "Reason    :" << e.what();
        return false;
    }

}

bool TestApplication::commit_resources()
{
    for (auto& vbo : mVertexBufferList) {
        glBufferData(GL_ARRAY_BUFFER, vbo.get_byte_size(), vbo.get_buffer(), GL_STATIC_DRAW);  // Upload data to GPU
    }
    return true;
}

bool TestApplication::render()
{

    // Clear screen and set background color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);  // Draw the triangle
    glfwSwapBuffers(pWindow);
    return true;
}

bool TestApplication::update()
{
    glfwPollEvents();
    return true;
}

bool TestApplication::destroy()
{

    for (auto& vbo : mVertexBufferList) {
        auto vbo_uid = vbo.get_resource_id();
        glDeleteBuffers(1, &vbo_uid);
        vbo.release();
    }

    for (auto& vao : mVertexBufferList) {
        auto vao_uid = vao.get_resource_id();
        glDeleteVertexArrays(1, &vao_uid);
        vao.release();
    }
    this->pShaderProgram->release();
    this->mShaderList.clear();
    this->mVertexArrayObjectList.clear();
    this->mVertexBufferList.clear();
    glfwDestroyWindow(pWindow);
    glfwTerminate();
    delete pShaderProgram;
    // delete pWindow;
    this->is_active = false;
    return true;
}