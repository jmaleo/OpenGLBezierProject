#version 460 core
out vec4 FragColor;

in vec3 ourColor;
//uniform vec4 ourColor; //we set this variable in the OpenGL code.


void main()
{
    FragColor = vec4(ourColor, 1.0f);
    //FragColor = ourColor;
} 