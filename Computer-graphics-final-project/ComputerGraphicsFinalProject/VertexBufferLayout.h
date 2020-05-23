#pragma once

#include <vector>
#include <GL/glew.h>
#include "ErrorHandler.h"

typedef unsigned int uint;

// GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (const void*)(0)));
//                            index, count, type, normalized, size(stride),    bias(offset)

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	bool normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:
			return unsigned int(sizeof(GLfloat));
		case GL_INT:
		case GL_UNSIGNED_INT:
			return unsigned int(sizeof(GLint));
		case GL_BYTE:
		case GL_UNSIGNED_BYTE:
			return unsigned int(sizeof(GLbyte));
		}
		ASSERT(false);
		return 0;
	}

};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout() : m_Stride(0) {}
	~VertexBufferLayout();
	
	template<typename T>
	void Push(uint count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(uint count) 
	{
		m_Elements.push_back(VertexBufferElement{ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(uint count)
	{
		m_Elements.push_back(VertexBufferElement{ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<unsigned char>(uint count)
	{
		m_Elements.push_back(VertexBufferElement{ GL_UNSIGNED_BYTE, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexBufferElement> GetElements() const& { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }
};

