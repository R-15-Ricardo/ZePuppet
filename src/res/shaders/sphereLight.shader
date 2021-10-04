#shader vertex
#version 460 core

layout(location = 0) in vec4 position;

uniform mat4 f_Projection;
uniform mat4 f_View;
uniform mat4 f_Model;

void main ()
{
	gl_Position = (f_Projection * f_View * f_Model) * position;
}

#shader fragment
#version 460 core

layout(location = 0) out vec4 color;

uniform vec4 u_LightColor;
void main ()
{
	color = u_LightColor;
}
