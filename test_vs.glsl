#version 400
uniform mat4 m_transform;

in vec3 vertex_position;
in vec3 vertex_colour;

out vec3 colour;

void main() {
  colour = vertex_colour;
  gl_Position = vec4(vertex_position, 1.0)*m_transform;
};