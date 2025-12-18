#version 430 core
layout (location = 0) in vec3 pos;

layout(std140, binding = 0) uniform in_ubo
{
	mat4 projection;
	mat4 model;
} ubo;

void main()
{
	gl_Position = ubo.projection * ubo.model * vec4(pos, 1.0f);
}
