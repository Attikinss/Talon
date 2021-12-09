#shader-type vertex
#version 450 core

layout(location = 0) in float a_PosX;
layout(location = 1) in float a_PosY;
layout(location = 2) in float a_PosZ;

void main()
{
	gl_Position = vec4(a_PosX, a_PosY, a_PosZ, 1.0);
}

#shader-type fragment
#version 450 core

out vec4 FragmentColour;

void main()
{
	FragmentColour = vec4(0.8, 0.2, 0.5, 1.0);
}
