#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;

uniform vec3 objectColor;
uniform vec3 lightColor;

out vec3 Color;

const float ambientStrength = 0.1f;
const float specularStrength = 0.5f;
const float shininess = 32;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);

    vec3 viewPos = vec3(view * model * vec4(aPos, 1.0f));
    mat3 normalMat = mat3(transpose(inverse(view * model))); // Model matrix without scalling and translation (the "normal matrix")
    vec3 normal = normalize(normalMat * aNormal);
    vec3 lightViewPos = vec3(view * vec4(lightPos, 1.f));

    vec3 lightDir = normalize(lightViewPos - viewPos);
    vec3 viewDir = normalize(-viewPos);
    vec3 reflectDir = normalize(reflect(-lightDir, normal));

    // Diffuse
    float diff = max(dot(lightDir, normal), 0.0f);
    vec3 diffuse = diff * lightColor;

    // Specular
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), shininess);
    vec3 specular = spec * lightColor;

    // Ambient
    vec3 ambient = ambientStrength * lightColor;
    Color = (ambient + diffuse + specular) * objectColor;
}