<Shader>Vertex
#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;
out vec4 ourColor;
out vec2 TexCoord;
void main()
{
    gl_Position =projection*view*model*vec4(aPos, 1.0f);
    ourColor = vec4(1.0f);
    TexCoord = aTexCoord;
}
<Shader>Fragment
#version 410 core
in vec4 ourColor;
in vec2 TexCoord;
out vec4 FragColor;
uniform sampler2D ourTexture;
uniform float transparency;
uniform vec3 color;
vec3 colorAUsar;
void main()
{
    colorAUsar = color;
    vec4 tex = texture(ourTexture,TexCoord).xyza;
    FragColor = vec4(tex.x+colorAUsar.x,tex.y+colorAUsar.y,tex.z+colorAUsar.z,(tex.a * transparency));
    if(FragColor.a < 0.1f)
    {
        discard;
    }
} 