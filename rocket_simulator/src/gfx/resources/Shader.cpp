#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "../../utils/logging/ConsoleLogger.h"
Shader::Shader(const char* src, const char* shaderName, ResourceType type, bool srcIsPath) : OpenGLResource(type)
{
    if (srcIsPath) {
        //load the file content
        std::ifstream file;
        std::stringstream ss;
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            file.open(src);
            ss << file.rdbuf();
            file.close();
            this->mShaderPath = src;
            this->mShaderSrcCode = ss.str();
            this->mShaderName = std::string(shaderName);
        }
        catch (std::ifstream::failure& e) {
            std::stringstream ss;
            ss << "SHADER_LOADING_ERROR: Failed to open Shader Source File at path : " << src << "\n";
            Logger::get_instance().logError(ss.str());
            this->mShaderSrcCode = std::string();
            this->mShaderPath = std :: string(src);
            this->mShaderName = std::string("FAILED TO LOAD!");
        }
    }
    else {
        this->mShaderSrcCode =      std::string(src);
        this->mShaderName    =      std::string(shaderName);
        this->mShaderPath    =      std::string("");
    }
}

const char* Shader::get_shader_source_code() const noexcept
{
    if (mShaderName == "FAILED TO LOAD!") return nullptr;
    else return mShaderSrcCode.c_str();
}

const char* Shader::get_shader_path() const noexcept
{
    return mShaderPath.c_str();
}

const char* Shader::get_shader_name() const noexcept
{
    return mShaderName.c_str();
}
