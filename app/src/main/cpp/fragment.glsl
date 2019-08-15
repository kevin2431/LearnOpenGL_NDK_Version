#version 300 es
precision mediump float;

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

//uniform sampler2D ourTexture;
// 两个纹理单元
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
//"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
 //   FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}