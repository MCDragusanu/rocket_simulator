#pragma once
#include <iostream>
#include <string>
#include <memory>


#include "../../../include/glad/glad.h"
#include "../../../include/glfw/glfw3.h"


namespace Resources {
	enum class ResourceType {
		BUFFER_VERTEX,
		BUFFER_INDEX,

		ARRAY_VERTEX_OBJECT,

		SHADER_MANAGER,
		SHADER_VERTEX,
		SHADER_FRAGMENT,
	};
	namespace Utils {
		 
	}
	class OpenGLResource {
	public:

		OpenGLResource(ResourceType type);
		OpenGLResource(GLuint uid, ResourceType type);
		
		GLuint					get_resource_id() const noexcept;
		ResourceType			get_resource_type() const noexcept;
		void					set_resouce_id(GLuint uid);
		virtual					void release() = 0;
		static const char * resource_type_to_string(int num) {
			switch (num) {
			case 0: return "BUFFER_VERTEX";
			case 1: return "BUFFER_INDEX";
			case 2: return "ARRAY_VERTEX_OBJECT";
			case 3: return "SHADER_MANAGER";
			case 4: return "SHADER_VERTEX";
			case 5: return "SHADER_PIXEL";
			default: return "Invalid ResourceType"; // Invalid input
			}
		}
	protected:
		GLuint mUid;
		ResourceType mResourceType;
	private:
		static GLuint index;
		static GLuint issue_next_uid();
	};

	class Shader : public OpenGLResource
	{
		friend class ShaderProgram;
	public:

		Shader(const char* src, 
			   const char* shaderName, 
			   ResourceType type, 
			   bool srcIsPath = true);
		Shader(ResourceType type);
		const char*			get_shader_source_code()const noexcept;
		const char*			get_shader_path() const noexcept;
		const char*			get_shader_name() const noexcept;
		void				release()override;
	protected:
		std::string    mShaderSrcCode;
		std::string	   mShaderPath;
		std::string	   mShaderName;
	};

	class ShaderProgram : public OpenGLResource
	{
	public:
		ShaderProgram();

		bool				compile_shader(Shader& shader, std::ostream& outputLog = std::cout)const;
		bool				isLinked()const noexcept;
		void				link_program();
		void				run_program();
		void				release()override;
	protected:
		GLuint issue_handle(const Shader& shader, std::ostream& outputLog)const;
	private:
		bool mLinkedState;
	};
	
	class VertexBuffer : public OpenGLResource
	{
	public:

		VertexBuffer(std::unique_ptr<float[]>&& buffer, 
					 size_t vertexCount, 
					 size_t vertexStride,
					 int normalization = 0);

		VertexBuffer(size_t vertexCount, 
					 size_t vertexStride, 
					 int normalization = 0);

		VertexBuffer(VertexBuffer&& other);
		VertexBuffer& operator=(VertexBuffer&& other);

		VertexBuffer& operator=(VertexBuffer& other) = delete;
		VertexBuffer(const VertexBuffer& other) = delete;
		VertexBuffer operator=(VertexBuffer other) = delete;


		const float*		get_buffer() const noexcept;
		float				at(size_t index) const;
		float&				at(size_t index);

		float				operator[](size_t index) const;
		float&				operator[](size_t index);

		size_t				get_float_count() const noexcept;
		size_t				get_vertex_stride() const noexcept;
		size_t				get_vertex_count() const noexcept;
		size_t				get_byte_size()const noexcept;

		void				print_buffer_content()const noexcept;
		void				release()override;
	protected:
		std::unique_ptr<float[]>		pBuffer;
		size_t							mVertexCount;
		size_t							mVertexStride;
		size_t							mFloatCount;
		size_t							mByteSize;
		int								mWithNormalisation;
	};

	class VertexArrayObject : public OpenGLResource {
	public:
		VertexArrayObject( size_t offset ,size_t vertexCount , size_t vertex_stride , int vertexType = GL_FLOAT);
		size_t				get_vertex_count() const noexcept;
		size_t				get_vertex_stride() const noexcept;
		size_t				get_vertex_offset() const noexcept;
		int					get_vertex_type() const  noexcept;

		void				release()override;
	private:
		size_t mVertexOffset;
		size_t mVertexCount;
		size_t mVertexStride;
		size_t mVertexType;
	};
};