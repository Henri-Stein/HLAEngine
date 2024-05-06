#version 330 core

in vec3 color;
uniform vec4 uColor;

out vec4 FragColor;


void main()
{
   // FragColor = vec4(color, 1.0f);
   FragColor = mix(vec4(color.rgb, 1.), uColor, 0.5);
   // FragColor = vec4(1.0f, 1.0f, 0.0f,1.0f);
   // FragColor = uColor;
   // return 1;
}
