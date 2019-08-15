//
// Created by zx on 19-8-15.
//
//
// Created by zx on 19-8-14.
//

#include <jni.h>
#include <string>
#include <iostream>
#include <android/log.h>

#include "game.h"
//#include <GLES2/gl2.h>
#include <GLES3/gl3.h>

#include "shader_common.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//#define  LOG_TAG    "libgl2jni"
//#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
//#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


// 用于索引的顶点
float vertices[] = {
        // position     // color    // texture coords
        0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,     // top right
        0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,     // bottom right
        -0.5f, -0.5f,0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,     // bottom left
        -0.5f, 0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f,     // top right
};

// 索引数组
unsigned int indices[] = {
        0,1,3,
        1,2,3
};

unsigned int VBO, VAO, EBO;

//unsigned int vertexShader, fragmentShader, shaderProgram;
unsigned int texture;

// 放到包里面读取， sdka读取方式是实现了的
// 怎么在res里面读取文件， native的方式
Shader ourShader("/data/data/com.example.airhockey_cpp/vertex.glsl", "/data/data/com.example.airhockey_cpp/fragment.glsl");


void on_surface_created() {
    // set vertex data and buffer attribute
    // --------------------------------------------------
    // VAO VBO 初始化
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8* sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // 颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8* sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    // 纹理属性
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8* sizeof(float), (void*)(6* sizeof(float)));
    glEnableVertexAttribArray(2);

    // 解绑 safe操作
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // 加载和创建纹理
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // 设定纹理wrapper参数
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // 纹理过滤
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // 加载image 创造纹理 生成mipmaps
    int width, height, nrChannels;
    std::string filename = "/data/data/com.example.airhockey_cpp/wall.jpg";
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);

    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else {
        LOGE("Failed to load texture\n");
    }
    stbi_image_free(data);

}

void on_surface_changed(int weight, int height) {
    // No-op
    glViewport(0,0, weight, height);
}

void on_draw_frame() {

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // bind texture
    glBindTexture(GL_TEXTURE_2D, texture);

    // 三角形
    //glUseProgram(shaderProgram);
    ourShader.use();

    glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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


