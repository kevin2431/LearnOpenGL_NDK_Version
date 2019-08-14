//
// Created by zx on 19-8-14.
//

#include <jni.h>
#include <string>
#include <iostream>
#include <android/log.h>
#include <ctime>
#include <cmath>

#include "game.h"
//#include <GLES2/gl2.h>
#include <GLES3/gl3.h>

#include "shader_common.h"

#define  LOG_TAG    "libgl2jni"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


// 着色器代码
// 要指定glsl版本  然后fragment shader需要定义精度才可以使用
// layout 可以代替glgetattributionLocation
//const char *vertexShaderSource = "#version 300 es\n"
//                                 "layout (location = 0) in vec3 aPos;\n     "   //位置变量的属性位置是0
//                                 "layout (location = 1) in vec3 aColor;\n "       // 颜色变量的属性位置是1
//                                 "out vec3 ourColor;\n"
//                                 "void main()\n"
//                                 "{\n"
//                                 "   gl_Position = vec4(aPos, 1.0);\n"
//                                 "   ourColor = aColor;\n"
//                                 //"vertexColor = vec4(0.5,0.0,0.0,1.0);\n"
//                                 "}\0";
//const char *fragmentShaderSource = "#version 300 es\n"
//                                   "precision mediump float;\n"
//                                   "out vec4 FragColor;\n"
//                                   "in vec3 ourColor;\n"
//                                   //"in vec4 vertexColor;\n"
//                                   "void main()\n"
//                                   "{\n"
//                                   //"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//                                   "FragColor = vec4(ourColor, 1.0);\n"
//                                   "}\n\0";

// 三角形数组 标准化坐标
float vertices[] = {
        // 位置 颜色 放在一起
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f,0.0f,   0.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f
};
// 用于索引的顶点
//float vertices[] = {
//        0.5f, 0.5f, 0.0f,
//        0.5f, -0.5f, 0.0f,
//        -0.5f, -0.5f,0.0f,
//        -0.5f, 0.5f, 0.0f
//};

// 索引数组
//unsigned int indices[] = {
//        0,1,3,
//        1,2,3
//};

unsigned int VBO, VAO, EBO;

unsigned int vertexShader, fragmentShader, shaderProgram;

// 放到包里面读取， sdka读取方式是实现了的
// 怎么在res里面读取文件， native的方式
Shader ourShader("/data/data/com.example.airhockey_cpp/vertex.glsl", "/data/data/com.example.airhockey_cpp/fragment.glsl");


void on_surface_created() {
    //glClearColor(1.0f, 0.0f, 0.0f, 0.0f);

    // build and compile our shader program
    // ------------------------------------
    // vertex shader
//    vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//    glCompileShader(vertexShader);
//    // check for shader compile errors
//    int success;
//    char infoLog[512];
//    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//    if (!success)
//    {
//        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//        //std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//        LOGE("Could not compile shader :\n%s\n", infoLog);
//    }
//
//    // fragment shader
//    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//    glCompileShader(fragmentShader);
//    // check for shader compile errors
//    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//    if (!success)
//    {
//        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//        //std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//        LOGE("Could not compile shader :\n%s\n", infoLog);
//    }
//
//    // link shaders
//    shaderProgram = glCreateProgram();
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    glLinkProgram(shaderProgram);
//    // check for linking errors
//    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//    if (!success) {
//        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//        //std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
//        LOGE("Could not compile program :\n%s\n", infoLog);
//    }
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);



    // set vertex data and buffer attribute
    // --------------------------------------------------
    // VAO VBO 初始化
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6* sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // 颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6* sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    // 解绑 safe操作
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // 线框模式 好像没有哦
}

void on_surface_changed(int weight, int height) {
    // No-op
    glViewport(0,0, weight, height);
}

void on_draw_frame() {

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // 三角形
    //glUseProgram(shaderProgram);
    ourShader.use();

    // 传递cpu中的颜色到gpu
//    float timeValue  = (float)std::clock();     //c++11 应该用chrono计时
//    float greenValue = std::sinf(timeValue)/2.0f + 0.5f;
//    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
//    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_airhockey_1cpp_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}


extern "C"
JNIEXPORT void JNICALL
Java_com_example_airhockey_1cpp_GameLibJNIWrapper_on_1surface_1created(JNIEnv *env, jclass type) {

// TODO
on_surface_created();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_airhockey_1cpp_GameLibJNIWrapper_on_1surface_1changed(JNIEnv *env, jclass type,
        jint width, jint height) {

// TODO
on_surface_changed(width, height);

}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_airhockey_1cpp_GameLibJNIWrapper_on_1draw_1frame(JNIEnv *env, jclass type) {

// TODO
on_draw_frame();
}

