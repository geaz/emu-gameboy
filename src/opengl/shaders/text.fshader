#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture2D;
uniform vec4 textColor;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(texture2D, TexCoord).r);
    FragColor = textColor * sampled;
}