#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 4) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    FragPos = vec3(model * vec4(aPos, 1.0f));

    mat3 normalMat = mat3(transpose(inverse(model))); // Model matrix without scalling and translation (the "normal matrix")
    Normal = normalMat * aNormal;
    TexCoords = aTexCoords;
    // LightPos = vec3(view * vec4(lightPos, 1.f));
}