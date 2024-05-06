#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 uTransform;
// uniform mat4 model;
// uniform mat4 view;
// uniform mat4 projection;

out vec3 color;

void main()
{
    color = aColor;
    gl_Position = uTransform * vec4(aPos, 1.0f);
}