#version 430 core
layout (location = 0) in vec3 pos;

layout(std140, binding = 0) uniform in_ubo
{
	mat4 projection;
	mat4 model;
	vec4 color;
} ubo;

out vec4 color;

void main()
{
	gl_Position = ubo.projection * ubo.model * vec4(pos, 1.0f);
	color = ubo.color;
}
