#shader vertex
#version 430 core
layout (location = 0) in vec4 inPos;
layout (location = 1) in vec4 inNormal;
layout (location = 2) in vec2 inTextureCoords;

uniform mat4 Projection;
uniform mat4 ModelView;

void main()
{
	gl_Position = Projection * ModelView * vec4(inPos.xyz, 1.0);
}

#shader fragment
#version 430 core

out vec4 color;

void main()
{
    color = vec4(1, 0.7, 0, 1); // sun-ish color 
}