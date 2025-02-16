#pragma once

#include <ostream>
#include <iostream>
#include <string>
#include "../../../include/glfw/glfw3.h"
#include <assert.h>
class OpenGLErrorHandler
{
public:
    
    explicit OpenGLErrorHandler() = default;
   
    void clear_errors() {
        while (glGetError() != GL_NO_ERROR);
    }

    unsigned int get_current_error() const noexcept {
        return glGetError();
    }

    void print_errors(std::ostream& os = std::cout) {
        bool errors_found = false;
        unsigned int error;
        do {
            error = glGetError();
            if (error != GL_NO_ERROR) {
                errors_found = true;
                os << "[Error Code: " << error << "] "
                    << translate_open_gl_error(error) << "\n";
            }
        } while (error != GL_NO_ERROR);

        if (!errors_found) {
            os << "No OpenGL errors detected.\n";
        }
    }

    std::string translate_open_gl_error(unsigned int error_code) const {
        switch (error_code) {
        case 0x0500:
            return "Name: GL_INVALID_ENUM\nExplanation: Given when an enumeration parameter is not a legal enumeration for that function.";
        case 0x0501:
            return "name: GL_INVALID_VALUE\nexplanation: Given when a value parameter is not a legal value for that function.";
        case 0x0502:
            return "name: GL_INVALID_OPERATION\nexplanation: Given when the set of state for a command is not legal for the parameters given to that command.";
        case 0x0503:
            return "name: GL_STACK_OVERFLOW\nexplanation: Given when a stack pushing operation causes a stack overflow.";
        case 0x0504:
            return "name: GL_STACK_UNDERFLOW\nexplanation: Given when a stack popping operation causes a stack underflow.";
        case 0x0505:
            return "name: GL_OUT_OF_MEMORY\nexplanation: Given when there is not enough memory left to execute the command.";
        case 0x0506:
            return "name: GL_INVALID_FRAMEBUFFER_OPERATION\nexplanation: Given when the framebuffer object is not complete.";
        case 0x0507:
            return "name : GL_CONTEXT_LOST\nexplanationGiven if the OpenGL context has been lost, due to a graphics card reset.";
                
        default:
            return "OPEN_GL_UNKNOWN_ERROR\nexplanation: An unknown error occurred.";
        }
    }

    static OpenGLErrorHandler getInstance() {
        static OpenGLErrorHandler _instance;
        return _instance;
    }
private:
    

} ;



#ifdef _DEBUG
#define GL_CALL(function_call)                                                                      \
        OpenGLErrorHandler::getInstance().clear_errors();                                                          \
        function_call;                                                                              \
        {unsigned int last_error =  OpenGLErrorHandler::getInstance().get_current_error();                           \
        do {                                                                                        \
                                                                                                    \
            if (last_error != GL_NO_ERROR) {                                                        \
                std::cout                                               \
                          << "[Error Code: " << last_error << "] "                                  \
                          <<  OpenGLErrorHandler::getInstance().translate_open_gl_error(last_error) << "\n"         \
                          << "Line: " << __LINE__ << "\n"                                           \
                          << "File: " << __FILE__ << "\n";                                          \
            }                                                                                       \
        } while (last_error != GL_NO_ERROR);     }                                                   
#else
#define GL_CALL(function_call) function_call
#endif

#ifdef _DEBUG
#define CHECK(expresion , failure_message)         \
        if(expresion){                            \
            std :: cerr << failure_message<<"\n";  \
        }
#endif