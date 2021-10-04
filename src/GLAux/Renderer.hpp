#pragma once

#include <GL/glew.h>
#include <assert.h>

#include "Vertex.hpp"
#include "Shader.hpp"

#define INT2VOIDP(i) (void*)(uintptr_t)(i)

#define ASSERT(x) if (!(x)) assert(false)

#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLCheckError())

void GLClearError();
bool GLCheckError();

class Renderer
{
    public:
        Renderer(float r, float g, float b);
        void Clear() const;
        void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    
    private:
        float clear_r;
        float clear_g;
        float clear_b;
};