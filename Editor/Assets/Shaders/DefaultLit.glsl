#shader-type vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;

uniform mat4 u_ModelMatrix;
uniform mat3 u_NormalMatrix;
uniform mat4 u_ViewProjectionMatrix;

out VertexData
{
	vec3 FragPosition;
	vec3 Normal;
} vertexOut;

void main()
{
	gl_Position = u_ViewProjectionMatrix * u_ModelMatrix * vec4(a_Position, 1.0);

	vertexOut.FragPosition = vec3(u_ModelMatrix * vec4(a_Position, 1.0));
	vertexOut.Normal = normalize(u_NormalMatrix * a_Normal);
}

#shader-type fragment
#version 450 core

out vec4 FragColour;

uniform vec3 u_ViewPosition;
uniform vec3 u_AmbientLightColour;
uniform vec3 u_LightDirection;

in VertexData
{
	vec3 FragPosition;
	vec3 Normal;
} vertexIn;

vec3 CalculateDirectionalLight(vec3 dirToView)
{
	vec3 dirToLight = normalize(-u_LightDirection);

	/* -------------- AMBIENT -------------- */
	vec3 ambient = u_AmbientLightColour;

	/* -------------- DIFFUSE -------------- */
	float ndl = max(dot(vertexIn.Normal, dirToLight), 0.0);
	vec3 diffuse = vec3(1.0) * ndl;

	/* -------------- SPECULAR ------------- */
	vec3 reflectDirection = reflect(-dirToLight, vertexIn.Normal);
	float vdr = max(dot(dirToView, reflectDirection), 0.0);
	vdr = pow(vdr, 32.0);
	vec3 specular = vec3(1.0) * vdr;

	return ambient + diffuse + specular;
}

void main()
{
	vec3 dirToView = normalize(u_ViewPosition - vertexIn.FragPosition);
	vec3 result = CalculateDirectionalLight(dirToView);

	FragColour = vec4(result, 1.0);
}
