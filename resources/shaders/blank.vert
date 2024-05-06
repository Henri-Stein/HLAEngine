#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aTangent;
layout (location = 3) in vec4 aCol;
layout (location = 4) in vec2 aTexCo;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 vPos;
out vec3 vNormal;
out vec3 vTangent;
out vec4 vCol;
out vec2 vTexCo;

void main()
{
    vPos = aPos;
    vNormal = aNormal;
    vTangent = aTangent;
    vCol = aCol;
    vTexCo = aTexCo;

    gl_Position = projection * view * model * vec4(aPos, 1.0f);
}