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


const int MAX_LIGHTS = 10;
uniform int lightTypes[MAX_LIGHTS];
uniform vec3 lightPositions[MAX_LIGHTS];    // For point lights
uniform vec3 lightColors[MAX_LIGHTS];
uniform vec3 lightDirections[MAX_LIGHTS];


uniform vec3 ambient_color;
uniform vec3 diffuse_color;
uniform vec3 specular_color;
uniform float shininess;

out vec4 fragPosLightSpace;
uniform mat4 lightSpaceMatrix;

void main() {
    vec3 fragPos = vec3(m * vec4(in_position, 1.0));
    vec4 position_cameraSpace = v * m * vec4(in_position, 1.0);
    vec4 normal_cameraSpace = vec4(normalize(mat3(transpose(inverse(v * m))) * normal), 0);
    texCoord = in_texCoord;
    color = ambient_color ;
     for (int i = 0; i < MAX_LIGHTS; i++) {
         vec4 vertexToLight = vec4(0);
         if (lightTypes[i] == 0) {
             vertexToLight = normalize(v * vec4(lightPositions[i], 1) - position_cameraSpace);
         } else if (lightTypes[i] == 1) {
             // Dir Light
             vertexToLight = normalize(v * vec4(-lightDirections[i], 0));
         }

       float diffuseIntensity = max(0.0, dot(vertexToLight, normal_cameraSpace));
       color += max(vec3(0), lightColors[i] * diffuse_color * diffuseIntensity);

       vec4 lightReflection = normalize(-reflect(vertexToLight, normal_cameraSpace));
       vec4 eyeDirection = normalize(vec4(0,0,0,1) - position_cameraSpace);
       float specIntensity = pow(max(0.0, dot(eyeDirection, lightReflection)), shininess);
       color += max (vec3(0), lightColors[i] * specular_color * specIntensity);
    //color = vec3(normal_cameraSpace.xyz);
     }

    fragPosLightSpace  = lightSpaceMatrix * vec4(fragPos, 1.0);
    gl_Position = p *position_cameraSpace;
}
