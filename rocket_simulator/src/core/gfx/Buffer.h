#pragma once
#include <string>
#include <vector>


namespace Core::Gfx {

	enum class DataType {
		None = 0,
		Float,
		Float2,
		Float3,
		Float4,
		Mat2,
		Mat3,
		Mat4,
		Int,
		Int2,
		Int3,
		Int4
	};

	struct BufferLayoutElement {
		std::string tag;
		DataType type;
		size_t byteSize;
		size_t offset;
		bool normalised; 
		static size_t getDataTypeByteSize(DataType type);
		BufferLayoutElement(const std::string& tag, DataType type);
		 size_t getElementCount() const noexcept;
	};

	class BufferLayout {
	public:
		BufferLayout();
		BufferLayout(const std::vector<BufferLayoutElement>& elements);
		BufferLayout(std::vector<BufferLayoutElement>&& elements);
		inline const std::vector<BufferLayoutElement>& getElements() const noexcept {
			return this->mElements;
		}
		inline size_t getStride() {
			return this->mStride;
		}

		std::vector <BufferLayoutElement>::iterator begin()  ;
		std::vector <BufferLayoutElement>::iterator end();

		std::vector <BufferLayoutElement>::const_iterator cbegin() const ;
		std::vector <BufferLayoutElement>::const_iterator cend()const;
	private:
		void calculateOffsetAndStride();
		std::vector<BufferLayoutElement> mElements;
		size_t mStride = { 0 };
	};

	struct VertexBuffer {


		static VertexBuffer* create(float* data, size_t byteSize);
		virtual ~VertexBuffer() {};
		virtual void bind() = 0;
		virtual void unBind() = 0;

		virtual	void setLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& getLayout() const noexcept = 0;
	};

	struct IndexBuffer {

		static IndexBuffer* create(unsigned int* data, size_t indexCount);

		virtual ~IndexBuffer() {};
		virtual void bind() = 0;
		virtual void unBind() = 0;
		virtual size_t getCount()const noexcept = 0;

	};
}