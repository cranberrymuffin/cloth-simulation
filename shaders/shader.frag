#version 330 core

in vec2 texCoord;
in vec3 color;
in vec4 fragPosLightSpace;
in vec4 fragPorjectorSpace;
//in vec4 position_cameraSpace;
//in vec4 normal_cameraSpace;

in vec3 fragPos;
in vec3 fragNormal;


//uniform sampler2D tex;
uniform sampler2D shadowMap;
uniform sampler2D texProj;

out vec4 fragColor;

const int MAX_LIGHTS = 10;
//uniform int lightTypes[MAX_LIGHTS];
uniform vec3 lightPositions[MAX_LIGHTS];    // For point lights
uniform vec3 lightColors[MAX_LIGHTS];
//uniform vec3 lightDirections[MAX_LIGHTS];

uniform vec3 ambient_color;
uniform vec3 diffuse_color;
uniform vec3 specular_color;
uniform float shininess;

uniform mat3 normalMatrix;

uniform vec3 mylightColor;


bool shadowCalculation(in vec4 fragpos)
{
    vec3 projCoords = fragpos.xyz / fragpos.w;
    projCoords = projCoords * 0.5 + 0.5;
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;

    float bias = 0.005;
    if( currentDepth  - bias> closestDepth )
    {

        return true;
    }
    else
    {

        return false;
    }


}

void main() {

    vec3 normal = normalize( normalMatrix * fragNormal);

    float visibility = 1.0;
    bool inShadow = shadowCalculation(fragPosLightSpace);

    vec3 result = ambient_color;
     for (int i = 0; i < MAX_LIGHTS; i++) {
          vec4 vertexToLight = vec4(0);
          vertexToLight = normalize( vec4(lightPositions[i], 1.0) - vec4(fragPos,1.0));
          float diffuseIntensity = max(0.0, dot(vertexToLight.xyz, normal));
          vec3 diffColor= max(vec3(0), lightColors[i] * diffuse_color * diffuseIntensity);

          if(inShadow)
          {
            visibility = 0.25;
          }
           result += ( diffColor *visibility) ;

          vec4 lightReflection = normalize(-reflect(vertexToLight, vec4(normal,0.0)));
          vec4 eyeDirection = normalize(vec4(lightPositions[i],1.0) - vec4(fragPos,1.0));
          float specIntensity = pow(max(0.0, dot(eyeDirection, lightReflection)), shininess);
          vec3 specularColor = (vec3(0), lightColors[i] * specular_color * specIntensity);
         result += specularColor;


    }

     vec4 textureColorProj  =  vec4(0.0);
     if(fragPorjectorSpace.z > 0.0)
     {
         textureColorProj = textureProj(texProj, fragPorjectorSpace);
     }

    //result = mix(textureColorProj.rgb,result,0.9f);
     float prjTextVisibility = 0.5;
     if(inShadow)
     {
         prjTextVisibility = 0.0;
     }
    fragColor = vec4(result,1.0) + textureColorProj * prjTextVisibility;// textureColorProj;


}
