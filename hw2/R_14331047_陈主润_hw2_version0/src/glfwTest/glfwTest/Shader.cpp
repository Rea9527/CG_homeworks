//
//  color_triangle.cpp
//  glfwTest
//
//  Created by 陈主润 on 01/03/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "stdafx.h"

#include <fstream>
#include <sstream>

#include "Shader.hpp"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {
    
    //create vertex shader
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexPath, NULL);
    glCompileShader(vertexShader);
    GLint success;
    GLchar errInfo[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, errInfo);
        std::cout << "ERROR: VERTEX SHADER CREATE!" << std::endl;
    }
    //fragment shader
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentPath, NULL);
    glCompileShader(fragmentShader);
    
    //create Program
    this->Program = glCreateProgram();
    glAttachShader(this->Program, vertexShader);
    glAttachShader(this->Program, fragmentShader);
    glLinkProgram(this->Program);
    //print if error
    glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->Program, 512, NULL, errInfo);
        std::cout << "ERROR: CREATE SHADER PROGRAM ERROR" << std::endl;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Use() {
    glUseProgram(this->Program);
}
