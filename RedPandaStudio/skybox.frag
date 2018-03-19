#version 450 core

uniform samplerCube skybox;

in vec3 tc;

layout (location = 0) out vec4 color;

void main(void)
{
    color = texture(skybox, tc);
    //color = vec4(0.0, 0.2, 0.6, 1.0);
}
