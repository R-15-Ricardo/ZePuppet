#shader vertex
#version 460 core

layout(location = 0) in vec4 position;
layout(location = 0) in vec3 vNormal;

out vec3 Normal;
out vec3 FragPos;

uniform mat4 f_Projection;
uniform mat4 f_View;
uniform mat4 f_Model;

void main ()
{
	gl_Position = (f_Projection * f_View * f_Model) * position;
	FragPos = vec3(f_Model * position);
	Normal = mat3(transpose(inverse(f_Model))) * vNormal;
}

#shader fragment
#version 460 core

in vec3 Normal;
in vec3 FragPos;
out vec4 color;

uniform vec4 u_LightColor;
uniform vec4 u_ObjectColor;
uniform vec3 lightPos;

void main ()
{
	float ambientStrenght = 0.1;
	float diffuseStrenght = 1.0;
	vec4 ambient = ambientStrenght * u_LightColor;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec4 diffuse = diffuseStrenght * diff * u_LightColor;

	color = (ambient + diffuse) * u_ObjectColor;
}
