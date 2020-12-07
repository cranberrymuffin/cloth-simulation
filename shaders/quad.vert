#version 330 core
layout (location = 0) in vec3 aPos;
<<<<<<< HEAD
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

void main()
{
    TexCoords = aTexCoords;
    gl_Position = vec4(aPos, 1.0);
=======

uniform mat4 lightSpaceMatrix;
uniform mat4 m;

void main()
{
    gl_Position = lightSpaceMatrix * m * vec4(aPos, 1.0);
>>>>>>> master
}
