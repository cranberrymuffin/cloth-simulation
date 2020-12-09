#version 330 core

in vec2 texCoord;
in vec3 color;
in vec4 fragPosLightSpace;


uniform sampler2D tex;
uniform sampler2D shadowMap;

out vec4 fragColor;


void main() {
   //fragColor = texture(tex, texCoord);

   vec4 textureColor = texture(tex, texCoord);

   vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
   projCoords = projCoords * 0.5 + 0.5;
   float closestDepth = texture(shadowMap, projCoords.xy).r;
   float currentDepth = projCoords.z;
   //float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;
   float bias = 0.005;
   if(currentDepth - bias> closestDepth)
   {
      fragColor = vec4(0);
   }else
   {
          fragColor = vec4(mix(textureColor.xyz, color, 0.5), 1);
   }
}
