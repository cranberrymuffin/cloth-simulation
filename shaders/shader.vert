#version 330 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 normal;   // Normal of the vertex
layout (location = 4) in vec2 aTexCoords;

layout(location = 5) in vec2 in_texCoord;

// Transformation matrices
uniform mat4 p;
uniform mat4 v;
uniform mat4 m;

out vec3 color;


out vec2 texCoord;
//out vec4 position_cameraSpace;
//out vec4 normal_cameraSpace;
out vec3 fragPos;
out vec3 fragNormal;

//const int MAX_LIGHTS = 10;
//uniform int lightTypes[MAX_LIGHTS];
//uniform vec3 lightPositions[MAX_LIGHTS];    // For point lights
//uniform vec3 lightColors[MAX_LIGHTS];
//uniform vec3 lightDirections[MAX_LIGHTS];


//uniform vec3 ambient_color;
//uniform vec3 diffuse_color;
//uniform vec3 specular_color;
//uniform float shininess;

out vec4 fragPosLightSpace;
uniform mat4 lightSpaceMatrix;

out vec4 fragPorjectorSpace;
uniform mat4 textureMatrix;



void main() {
    fragPos = vec3(m * vec4(in_position, 1.0));

    texCoord = in_texCoord;
    fragNormal =normal;

    fragPosLightSpace  = lightSpaceMatrix * vec4(fragPos, 1.0);
    fragPorjectorSpace =  textureMatrix *m * vec4(in_position, 1.0);

    gl_Position = p *v* vec4(fragPos,1.0);
}
