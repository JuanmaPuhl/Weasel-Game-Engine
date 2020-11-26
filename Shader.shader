<Shader>Vertex
#version 330 core
layout (location = 0) in vec3 aPos;

out vec4 vertexColor;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertexColor = vec4(0.5f,0.0f,0.0f,1.0f);
}
<Shader>Fragment
#version 330 core
in vec4 vertexColor;
uniform vec4 ourColor;
out vec4 FragColor;

void main()
{
    FragColor = ourColor;
} 