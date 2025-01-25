#version 460 core
in vec2 uv;
out vec4 FdfragColor;
uniform sampler2D text;
uniform vec2 textureTilling = vec2(1.0, 1.0);
uniform vec2 textureOffset = vec2(0.0, 0.0);
void main()
{
    FdfragColor = texture(text, uv * textureTilling + textureOffset);
};