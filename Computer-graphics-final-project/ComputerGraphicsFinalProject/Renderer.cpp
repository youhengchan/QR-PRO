#include <iostream>
#include "Renderer.h"
#include "ErrorHandler.h"

void Renderer::EnableBlending(void) const
{
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void Renderer::Draw(const VertexArray & vao, const IndexBuffer & ib, const Shader & shader) const
{
	shader.Bind();

	vao.Bind();

	ib.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}
