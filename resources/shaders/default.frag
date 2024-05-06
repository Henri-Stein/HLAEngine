#version 330 core

uniform sampler2D uTex0;
uniform sampler2D uTex1;

in vec2 texCoord;

out vec4 FragColor;


void main()
{
   FragColor = mix(texture(uTex0, texCoord), texture(uTex1, texCoord), -0.3f);
}
