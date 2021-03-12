<Shader>Vertex
#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
out vec2 TexCoord;
void main()
{
    //Se multiplica por dos porque el quad va de -0.5 a 0.5, de forma que el cuadrado tenga
    //tamaño 1 y pueda escalar lo que quiera.
    //Para que sea de pantalla completa entonces tiene que ser de -1 a 1.
    gl_Position =vec4(2.0f*aPos.x,2.0f*aPos.y,aPos.z, 1.0f);
    TexCoord = aTexCoord;
}
<Shader>Fragment
#version 410 core
in vec4 ourColor;
in vec2 TexCoord;
out vec4 FragColor;
uniform int pixelization;
uniform int pixelSize;
uniform int sharpen;
uniform float amount;

uniform sampler2D ourTexture;
void main()
{
    /* int pixelization = 0;
    int sharpen = 0;
    int pixelSize = 5;
    float amount = 0.8; */
    vec4 tex = texture(ourTexture,TexCoord).xyza;
    FragColor = tex; //Color original
    
    //Pixelization
    vec2 texSize  = textureSize(ourTexture, 0).xy;
    if(pixelization == 1)
    {
        //int pixelSize = 5;
        float x = int(gl_FragCoord.x) % pixelSize;
        float y = int(gl_FragCoord.y) % pixelSize;
        x = floor(pixelSize / 2.0) - x;
        y = floor(pixelSize / 2.0) - y;
        x = gl_FragCoord.x + x;
        y = gl_FragCoord.y + y;
        FragColor = texture(ourTexture, vec2(x, y)/texSize);  
    }
    
    //Sharpen
    if(sharpen == 1)
    {
        //float amount = 0.8;
        float neighbor = amount * -1;
        float center   = amount * 4 + 1;
        vec3 color = 
            texture(ourTexture, vec2(gl_FragCoord.x + 0, gl_FragCoord.y + 1) / texSize).rgb
            * neighbor
            + texture(ourTexture, vec2(gl_FragCoord.x - 1, gl_FragCoord.y + 0) / texSize).rgb
            * neighbor
            + texture(ourTexture, vec2(gl_FragCoord.x + 0, gl_FragCoord.y + 0) / texSize).rgb
            * center
            + texture(ourTexture, vec2(gl_FragCoord.x + 1, gl_FragCoord.y + 0) / texSize).rgb
            * neighbor
            + texture(ourTexture, vec2(gl_FragCoord.x + 0, gl_FragCoord.y - 1) / texSize).rgb
            * neighbor
            ;
        FragColor = vec4(color, texture(ourTexture, TexCoord).a);
    }
} 