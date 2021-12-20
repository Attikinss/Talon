#shader-type vertex
#version 450 core

layout(location = 0) in vec3 a_Position;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewProjectionMatrix;

void main()
{
	gl_Position = u_ViewProjectionMatrix * u_ModelMatrix * vec4(a_Position, 1.0);
}

#shader-type fragment
#version 450 core

out vec4 FragColour;

void main()
{
	FragColour = vec4(1.0, 0.0, 1.0, 1.0);
}
