#shader-type vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_UV;
layout(location = 3) in vec3 a_Tangent;
layout(location = 4) in vec3 a_BiTangent;

uniform mat4 u_ModelMatrix;
uniform mat3 u_NormalMatrix;
uniform mat4 u_ViewProjectionMatrix;

struct VertexData
{
	vec3 FragPosition;
	vec3 Normal;
	vec2 UV;
	vec3 Tangent;
	vec3 BiTangent;
};

layout(location = 0) out VertexData VertexOut;

void main()
{
	gl_Position = u_ViewProjectionMatrix * u_ModelMatrix * vec4(a_Position, 1.0);

	VertexOut.FragPosition = vec3(u_ModelMatrix * vec4(a_Position, 1.0));
	VertexOut.Normal = normalize(u_NormalMatrix * a_Normal);
	VertexOut.UV = a_UV;
	VertexOut.Tangent = a_Tangent;
	VertexOut.BiTangent = a_BiTangent;
}

#shader-type fragment
#version 450 core

struct VertexData
{
	vec3 FragPosition;
	vec3 Normal;
	vec2 UV;
	vec3 Tangent;
	vec3 BiTangent;
};

layout(location = 0) in VertexData VertexIn;

layout(location = 0) out vec4 FragColour;

uniform vec3 u_ViewPosition;
uniform vec3 u_AmbientLightColour;
uniform vec3 u_LightDirection;

uniform vec3 u_LightPosition;
uniform vec3 u_Attenuation;

uniform sampler2D u_AlbedoTex;
uniform sampler2D u_NormalTex;

vec3 CalcNormalTex()
{
	vec3 tangentNormal = texture(u_NormalTex, VertexIn.UV).rgb;

	tangentNormal = tangentNormal * 2.0 - 1.0;
	tangentNormal = normalize(tangentNormal);
	
	// Multiplier to normal "strength"
	tangentNormal.z *= 1.0;
	
	mat3 tbn = mat3(normalize(VertexIn.Tangent), normalize(VertexIn.BiTangent), normalize(VertexIn.Normal));

	return normalize(tbn * tangentNormal);
}

vec3 CalcDiffuse(vec3 dirToLight, vec3 normal)
{
	float ndl = max(dot(normal, dirToLight), 0.0);
	return texture(u_AlbedoTex, VertexIn.UV).rgb * ndl;
}

vec3 CalcSpecular(vec3 dirToView, vec3 dirToLight, vec3 normal)
{
	vec3 reflectDirection = reflect(-dirToLight, normal);
	float vdr = max(dot(dirToView, reflectDirection), 0.0);
	vdr = pow(vdr, 32.0);
	return vec3(1.0) * vdr;
}

vec3 CalculateDirLight(vec3 dirToView, vec3 normal)
{
	vec3 dirToLight = normalize(-u_LightDirection);
	
	vec3 ambient = texture(u_AlbedoTex, VertexIn.UV).rgb * u_AmbientLightColour;
	vec3 diffuse = CalcDiffuse(dirToLight, normal);
	vec3 specular = CalcSpecular(dirToView, dirToLight, normal);

	return ambient + diffuse + specular;
}

vec3 CalculatePointLight(vec3 dirToView, vec3 normal)
{
	vec3 dirToLight = normalize(u_LightPosition - VertexIn.FragPosition);

	/* ------------- ATTENUATION ----------- */
	float constant = max(u_Attenuation.x, 0.0);
	float linear = max(u_Attenuation.y, 0.0);
	float quadratic = max(u_Attenuation.x, 0.0);

	float distance = length(u_LightPosition - VertexIn.FragPosition) / 2.5f;
	float attenuation = constant + (linear * distance) + (quadratic * distance * distance);

	vec3 ambient = texture(u_AlbedoTex, VertexIn.UV).rgb * u_AmbientLightColour;
	vec3 diffuse = CalcDiffuse(dirToLight, normal);
	vec3 specular = CalcSpecular(dirToView, dirToLight, normal);
	return (ambient + diffuse + specular) / attenuation;
}

void main()
{
	vec3 dirToView = normalize(u_ViewPosition - VertexIn.FragPosition);
	vec3 normal = CalcNormalTex();

	// Directional Light
	vec3 dirLight = CalculateDirLight(dirToView, normal);

	// Point Light
	vec3 pointLight = CalculatePointLight(dirToView, normal);

	FragColour = vec4(dirLight + pointLight, 1.0);
}
