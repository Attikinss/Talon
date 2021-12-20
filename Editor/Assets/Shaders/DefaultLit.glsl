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

uniform vec3 u_LightPosition;
uniform vec3 u_Attenuation;

in VertexData
{
	vec3 FragPosition;
	vec3 Normal;
} vertexIn;

vec3 CalcDiffuse(vec3 dirToLight)
{
	float ndl = max(dot(vertexIn.Normal, dirToLight), 0.0);
	return vec3(1.0) * ndl;
}

vec3 CalcSpecular(vec3 dirToView, vec3 dirToLight)
{
	vec3 reflectDirection = reflect(-dirToLight, vertexIn.Normal);
	float vdr = max(dot(dirToView, reflectDirection), 0.0);
	vdr = pow(vdr, 32.0);
	return vec3(1.0) * vdr;
}

vec3 CalculateDirLight(vec3 dirToView)
{
	vec3 dirToLight = normalize(-u_LightDirection);
	
	vec3 ambient = u_AmbientLightColour;
	vec3 diffuse = CalcDiffuse(dirToLight);
	vec3 specular = CalcSpecular(dirToView, dirToLight);

	return ambient + diffuse + specular;
}

vec3 CalculatePointLight(vec3 dirToView)
{
	vec3 dirToLight = normalize(u_LightPosition - vertexIn.FragPosition);

	/* ------------- ATTENUATION ----------- */
	float constant = max(u_Attenuation.x, 0.0);
	float linear = max(u_Attenuation.y, 0.0);
	float quadratic = max(u_Attenuation.x, 0.0);

	float distance = length(u_LightPosition - vertexIn.FragPosition) / 2.5f;
	float attenuation = constant + (linear * distance) + (quadratic * distance * distance);

	vec3 ambient = u_AmbientLightColour;
	vec3 diffuse = CalcDiffuse(dirToLight);
	vec3 specular = CalcSpecular(dirToView, dirToLight);
	return (ambient + diffuse + specular) / attenuation;
}

void main()
{
	vec3 dirToView = normalize(u_ViewPosition - vertexIn.FragPosition);

	// Directional Light
	vec3 dirLight = CalculateDirLight(dirToView);

	// Point Light
	vec3 pointLight = CalculatePointLight(dirToView);

	FragColour = vec4(dirLight + pointLight, 1.0);
}
