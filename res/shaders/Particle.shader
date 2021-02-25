<Shader>Vertex
#version 410 core
layout (location = 0) in vec3 aPos; 
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoords;
out vec4 ParticleColor;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 offset;
uniform vec4 color;

void main()
{
    float scale = 5.0f;
    TexCoords = aTexCoord;
    ParticleColor = color;
    gl_Position = projection*view*vec4((aPos.xyz * scale)+offset, 1.0);
}
<Shader>Fragment
#version 410 core
in vec2 TexCoords;
in vec4 ParticleColor;
out vec4 ourColor;


void main()
{
    if(ParticleColor.a < 0.1)
        discard;
    ourColor = ParticleColor;
    
}  