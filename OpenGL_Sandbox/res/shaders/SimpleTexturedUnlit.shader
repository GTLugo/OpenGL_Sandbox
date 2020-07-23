#shader vertex
#version 410 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uv;

uniform mat4 u_MVP;

out vec2 v_UV;

void main() {
    gl_Position = u_MVP * position;
    v_UV = uv;
}

#shader fragment
#version 410 core

in vec2 v_UV;

uniform sampler2D u_Texture;

layout(location = 0) out vec4 color;

void main() {
    vec4 texColor = texture(u_Texture, v_UV);
    color = texColor;
}