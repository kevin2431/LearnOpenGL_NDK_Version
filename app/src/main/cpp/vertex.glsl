#version 300 es

layout (location = 0) in vec3 aPos;       //位置变量的属性位置是0
layout (location = 1) in vec3 aColor;        // 颜色变量的属性位置是1
out vec3 ourColor;

void main()
{
   gl_Position = vec4(aPos, 1.0);
   ourColor = aColor;
//"vertexColor = vec4(0.5,0.0,0.0,1.0);\n"
}
