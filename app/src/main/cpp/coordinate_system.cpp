//
// Created by zx on 19-8-15.
//

#include <jni.h>
#include <string>
#include <iostream>
#include <android/log.h>
#include <ctime>

#include "game.h"
//#include <GLES2/gl2.h>
#include <GLES3/gl3.h>

#include "shader_common.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// openg gl matrix
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
//float vertices[] = {
//        // positions          // texture coords
//        0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
//        0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
//        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
//        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left
//};
// 6个立方体 ，不需要用到索引了
float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

// 索引数组
//unsigned int indices[] = {
//        0,1,3,
//        1,2,3
//};

unsigned int VBO, VAO, EBO;

//unsigned int vertexShader, fragmentShader, shaderProgram;
//unsigned int texture;
unsigned int texture1, texture2;

// 放到包里面读取， sdka读取方式是实现了的
// 怎么在res里面读取文件， native的方式
Shader ourShader("/data/data/com.example.airhockey_cpp/vertex.glsl", "/data/data/com.example.airhockey_cpp/fragment.glsl");


void on_surface_created() {
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5* sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
//    // 颜色属性
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8* sizeof(float), (void*)(3* sizeof(float)));
//    glEnableVertexAttribArray(1);
    // 纹理属性
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5* sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

//    // 解绑 safe操作
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);

    // 加载和创建纹理
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    // 设定纹理wrapper参数
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // 纹理过滤
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // 加载image 创造纹理 生成mipmaps
    int width, height, nrChannels;
    std::string filename1 = "/data/data/com.example.airhockey_cpp/wall.jpg";

    stbi_set_flip_vertically_on_load(true);     // 翻转图像
    unsigned char *data = stbi_load(filename1.c_str(), &width, &height, &nrChannels, 0);

    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else {
        LOGE("Failed to load texture1\n");
    }
    stbi_image_free(data);

    // texture 2
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    // 设定纹理wrapper参数
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // 纹理过滤
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    std::string filename2 = "/data/data/com.example.airhockey_cpp/awesomeface.png";

    data = stbi_load(filename2.c_str(), &width, &height, &nrChannels, 0);

    if(data){
        // 这张图片有透明度， 所以读入需要rgba
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else {
        LOGE("Failed to load texture2\n");
    }
    stbi_image_free(data);

    // 告知采样器对应的纹理单元，只需要做一次
    ourShader.use();
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"),0);      // 手动设置
    ourShader.setInt("texture2", 1);    // 通过对应的类

    // 开启z缓冲 深度测试
    glEnable(GL_DEPTH_TEST);

}

void on_surface_changed(int weight, int height) {
    // No-op
    glViewport(0,0, weight, height);
}

void on_draw_frame() {

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // 清除深度缓冲
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    ourShader.use();

    // 不同坐标之间的变换
    glm::mat4 model = glm::mat4(1.0f);  // 保证初始化位单位阵
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    // 随时间变换
    model = glm::rotate(model, (float)std::clock()*glm::radians(50.0f)/100000.0f, glm::vec3(0.5f, 1.0f, 0.0f));
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));  // 物体负方向移动，相当于视野向前吧
    // 宽高比怎么获得
    projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);

    // 获取uniform的位置，并传递数据给着色器
    unsigned int modleLoc = glGetUniformLocation(ourShader.ID, "model");
    unsigned int viewLoc  = glGetUniformLocation(ourShader.ID, "view");
    unsigned int projectionLoc = glGetUniformLocation(ourShader.ID, "projection");
    // 数据传递的三种方式，setmat还没写
    glUniformMatrix4fv(modleLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
    //ourShader.setMat()
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
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





