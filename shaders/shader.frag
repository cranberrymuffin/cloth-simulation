#version 330 core

in vec2 texCoord;
in vec3 color;

uniform sampler2D tex;

out vec4 fragColor;

void main() {
    //fragColor = texture(tex, texCoord);
    fragColor = vec4(color,1.0);
}
