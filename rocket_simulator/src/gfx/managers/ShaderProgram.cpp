#include "ShaderProgram.h"
#include <cassert>
#include <iostream>



ShaderProgram::ShaderProgram() : OpenGLResource(ResourceType::SHADER_MANAGER) {
    GLuint shaderProgram = glCreateProgram();
    this->set_resouce_id(shaderProgram);
    std::cout << "Shader Program Uid issued: " << shaderProgram << "\n";
   
}

void ShaderProgram::run_program() {
  
    glUseProgram(this->get_resource_id());
}
bool ShaderProgram::compile_shader(Shader& shader, std::ostream& outputLog) const {
    if (shader.get_shader_source_code() == nullptr) {
        outputLog << "ERROR: Compiling Shader;\n";
        outputLog << "Reason: No source code found!\n";
        outputLog << "Shader Name: " << shader.get_shader_name() << "\n";
        outputLog << "Shader File Path: " << (shader.get_shader_path() != nullptr ? shader.get_shader_path() : "No Path Found!") << "\n";
        return -1;
    }

    GLuint shader_handle = issue_handle(shader, outputLog);
    if (shader_handle == -1) {
        return -1;
    }
    auto p_source_code = (shader.get_shader_source_code());
    glShaderSource(shader_handle, 1, &p_source_code, nullptr);
    glCompileShader(shader_handle);
    std::cout << shader.get_shader_name() << " compiled succesfully!\n";
    // Check for compilation errors
    int success;
    char infoLog[512];
    glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader_handle, 512, nullptr, infoLog);
        outputLog << "ERROR: Compiling Shader;\n";
        outputLog << "Reason: Compilation Failed!\n";
        outputLog << "Info: " << infoLog << "\n";
        outputLog << "Shader Name: " << shader.get_shader_name() << "\n";
        outputLog << "Shader File Path: " << (shader.get_shader_path() != nullptr ? shader.get_shader_path() : "No Path Found!") << "\n";
        return false;
    }

    // Attach shader to program and link it
    glAttachShader(this->get_resource_id(), shader_handle);
    glLinkProgram(this->get_resource_id());

    // Check if linking was successful
    glGetProgramiv(this->get_resource_id(), GL_LINK_STATUS, &success);
    glGetProgramInfoLog(this->get_resource_id(), 512, nullptr, infoLog);
    if (!success) {
        outputLog << "ERROR: Compiling Shader;\n";
        outputLog << "Reason: Failed to link Shader Program!\n";
        outputLog << "Info: " << infoLog;
        outputLog << "Shader Name: " << shader.get_shader_name() << "\n";
        outputLog << "Shader File Path: " << (shader.get_shader_path() != nullptr ? shader.get_shader_path() : "No Path Found!") << "\n";
        return false;
    }

    // Set the resource id for the shader and clean up
    shader.set_resouce_id(shader_handle);

    // The shader is no longer needed once it's linked to the program
    glDeleteShader(shader_handle);

    std::cout << shader.get_shader_name() << " attached succesfully!\n";
    return true; 
}

GLuint ShaderProgram::issue_handle(const Shader& shader, std::ostream& outputLog) const {
    unsigned int shader_type = -1;
    switch (shader.get_resource_type()) {
    case ResourceType::SHADER_VERTEX:
        shader_type = GL_VERTEX_SHADER;
        break;
    case ResourceType::SHADER_FRAGMENT:
        shader_type = GL_FRAGMENT_SHADER;
        break;
    default:
        shader_type = -1;
        break;
    }

    assert(shader_type != -1);  
    if (shader_type == -1) {
        outputLog << "ERROR: Issuing Handle for Shader;\n";
        outputLog << "Reason: Invalid Resource Type: " << OpenGLResource::resource_type_to_string((int)shader.get_resource_type()) << "\n";
        outputLog << "Shader Name: " << shader.get_shader_name() << "\n";
        return -1;
    }

    GLuint shader_handle = glCreateShader(shader_type);
    return shader_handle;
}
