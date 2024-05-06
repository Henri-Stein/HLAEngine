#version 330 core

in vec3 vPos;
in vec3 vNormal;
in vec3 vTangent;
in vec4 vCol;
in vec2 vTexCo;

out vec4 FragColor;

void main()
{
   // FragColor = vec4(vPos, 1.0f);
   // FragColor = vec4((vNormal +1.0f) * 0.5f, 1.0f);
   // FragColor = vec4(vTangent, 1.0f);
   // FragColor = vCol;
   FragColor = vec4(vTexCo, 0.0f, 1.0f);
}
