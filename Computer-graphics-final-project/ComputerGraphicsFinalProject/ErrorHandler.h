#pragma once

#include <GL/glew.h>

#define ASSERT(x) if (!(x)) __debugbreak();  // __ means the function is the kind of compileer intrinsic
// __debugbreak()��MSVC���������е����ú�����gcc��clangʧЧ
#define GLCall(x) GLClearError();\
		x;\
		ASSERT(GLLogCall(#x, __FILE__, __LINE__))

// �ڱ�дMacro��ʱ��β����\���治�ܼ��Ͽո�֮���ټ��ϻ��з��ţ���Ӧ��ֱ�ӻ���

void GLClearError();

void GLCheckError();

bool GLLogCall(const char* function, const char* file, int line);