#shader-type vertex
#version 450 core

layout(location = 0) in vec3 a_Position;

void main()
{
	gl_Position = vec4(a_Position, 1.0);
}

#shader-type fragment
#version 450 core

out vec4 FragmentColour;

uniform vec4 Colour;

void main()
{
	FragmentColour = Colour;
}
