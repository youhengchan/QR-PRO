#pragma once

#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer
{
public:
	void EnableBlending(void) const;
	void Draw(const VertexArray& vao, const IndexBuffer &ib, const Shader& shader) const;
	void Clear() const;
};