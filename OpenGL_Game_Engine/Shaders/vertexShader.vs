#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTextCoord;

out vec3 fragPos;
out vec3 normal;
out vec2 textCoord;


uniform mat4 model;
uniform mat4 view;
uniform mat4 proyeccion;
void main()
{
    gl_Position = proyeccion * view * model * vec4(aPos, 1.0f);

    normal = (model * vec4(aNormal, 0.0)).xyz;
    fragPos = vec3(model * vec4(aPos, 1.0));
    textCoord = aTextCoord;
}
