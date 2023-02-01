#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor; //The color variable has attribute position1

out vec3 ourColor;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = vec3(aColor.x, aColor.y, aColor.z);
}