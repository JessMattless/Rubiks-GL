#version 330 core

// Import vertex data
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vertexColor;

out vec3 fragmentColor;

// Define constant values for the mesh
uniform mat4 MVP;

void main() {
	// The output position of the vertex: MVP * position
	gl_Position = MVP * vec4(vPos, 1);

	fragmentColor = vertexColor;
}