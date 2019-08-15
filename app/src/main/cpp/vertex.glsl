#version 300 es

layout (location = 0) in vec3 aPos;       //位置变量的属性位置是0
//layout (location = 1) in vec3 aColor;        // 颜色变量的属性位置是1
layout (location = 1) in vec2 aTexCoord;

//out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 transform;

void main()
{
   gl_Position = transform*vec4(aPos, 1.0f);
//   ourColor = aColor;
   TexCoord = aTexCoord;
   // 传递矩阵后，纹理坐标,方向不同，写法也不同, 已经翻转了，就不要再做一次操作
   //TexCoord = vec2(aTexCoord.x, 1.0-aTexCoord.y);
}
