#version 300 es
precision mediump float;
out vec4 FragColor;
in vec3 ourColor;
//"in vec4 vertexColor;\n"\

void main()
{
//"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    FragColor = vec4(ourColor, 1.0);
}