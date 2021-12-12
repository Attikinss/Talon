#shader-type vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_UVs;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewProjectionMatrix;

out vec2 UVs;

void main()
{
	UVs = a_UVs;
	gl_Position = u_ViewProjectionMatrix * u_ModelMatrix * vec4(a_Position, 1.0);
}

#shader-type fragment
#version 450 core

out vec4 o_FragmentColour;

in vec2 UVs;

void main()
{
	o_FragmentColour = vec4(UVs, 0.0, 1.0);
}
