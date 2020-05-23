#pragma once

#include <GL/glew.h>

#define ASSERT(x) if (!(x)) __debugbreak();  // __ means the function is the kind of compileer intrinsic
// __debugbreak()是MSVC编译器特有的内置函数，gcc，clang失效
#define GLCall(x) GLClearError();\
		x;\
		ASSERT(GLLogCall(#x, __FILE__, __LINE__))

// 在编写Macro的时候尾部的\后面不能加上空格之后再加上换行符号，而应该直接换行

void GLClearError();

void GLCheckError();

bool GLLogCall(const char* function, const char* file, int line);