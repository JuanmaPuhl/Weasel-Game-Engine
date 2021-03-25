<Shader>Vertex
#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;
out vec2 TexCoord;
void main()
{
    gl_Position =projection*view*model*vec4(aPos.x,aPos.y,aPos.z, 1.0f);
    TexCoord = aTexCoord;
}
<Shader>Fragment
#version 410 core
in vec2 TexCoord;
out vec4 FragColor;
uniform sampler2D ourTexture;
uniform float transparency;
uniform vec4 color;
vec4 colorAUsar;
void main()
{
    colorAUsar = color;
    vec4 tex = texture(ourTexture,TexCoord).xyza;
    FragColor = vec4(0.0f);
    if(tex.a >=0.0f){
    if(colorAUsar.a > 0.0f)
        FragColor = vec4(tex.x+colorAUsar.x,tex.y+colorAUsar.y,tex.z+colorAUsar.z,((tex.a)* transparency+color.a));
    else
        FragColor = vec4(tex.x+colorAUsar.x,tex.y+colorAUsar.y,tex.z+colorAUsar.z,((tex.a)* transparency));
    }
    else{
        if(colorAUsar.a > 0.0f)
            FragColor = vec4(colorAUsar.x,colorAUsar.y,colorAUsar.z,(color.a));
        else
            FragColor = vec4(colorAUsar.x,colorAUsar.y,colorAUsar.z,0.0f);
    }
    if(FragColor.a <= 0.1f)
    {
        discard;
    }
} 