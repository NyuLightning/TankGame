#version 330

uniform mat4 pMatrix;
uniform mat4 mMatrix;
layout (location = 0) in vec4 vertexPosition;

void main()
{
        gl_Position = pMatrix*mMatrix*vertexPosition;
}
