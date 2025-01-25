#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUv;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec2 uv;
void main()
{
   vec4 vertexInLocalSpace = vec4(aPos.x, aPos.y, aPos.z, 1.0f);
   vec4 vertexInNDCSpace = vertexInLocalSpace * model * view * projection;

   gl_Position = vec4(vertexInNDCSpace.x, vertexInNDCSpace.y, vertexInNDCSpace.z, vertexInNDCSpace.w);
   uv = aUv;
}