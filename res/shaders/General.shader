<Shader>Vertex
#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
out vec2 TexCoord;
void main()
{
    gl_Position =vec4(aPos.x,aPos.y,aPos.z, 1.0f);
    TexCoord = aTexCoord;
}
<Shader>Fragment
#version 410 core
in vec4 ourColor;
in vec2 TexCoord;
out vec4 FragColor;
uniform sampler2D ourTexture;
void main()
{
    vec4 tex = texture(ourTexture,TexCoord).xyza;
    FragColor = tex;
    //FragColor = vec4(1.0f);
} 