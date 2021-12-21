#shader-type vertex
#version 450 core

layout(location = 0) in vec3 a_Position;

layout (std140, binding = 0) uniform CameraData
{
	uniform mat4 u_ViewProjectionMatrix;
	uniform vec3 u_ViewPosition;
};

uniform mat4 u_ModelMatrix;

void main()
{
	gl_Position = u_ViewProjectionMatrix * u_ModelMatrix * vec4(a_Position, 1.0);
}

#shader-type fragment
#version 450 core

layout(location = 0) out vec4 FragColour;

void main()
{
	FragColour = vec4(1.0, 0.0, 1.0, 1.0);
}
