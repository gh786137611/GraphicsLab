#version 330 core

in vec3 v_pos;
in vec3 v_color;

uniform mat4 modelViewProjection;

out vec3 f_color;
void main()
{
        gl_Position = modelViewProjection * vec4(v_pos, 1.f);
        f_color = v_color;
}
