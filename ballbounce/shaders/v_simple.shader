#version 330 core
layout(location = 0) in vec3 aPos; // the position variable has attribute position 0

out vec4 vertexColor; // specify a color output to the fragment shader

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform int type;



void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor
	switch (type) {
	case 0:
		vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // set the output variable to a red color
		break;
	case 1:
		vertexColor = vec4(0.0, 0.0, 0.5, 1.0); // set the output variable to a blue color
		break;
	}

}