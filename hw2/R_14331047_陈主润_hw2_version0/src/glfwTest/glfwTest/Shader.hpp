//
//  color_triangle.hpp
//  glfwTest
//
//  Created by 陈主润 on 01/03/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//


#ifndef shader_hpp
#define shader_hpp


#include <iostream>

#include <GL/glew.h>

class Shader {
public:
    // program id
    GLuint Program;
    // create vertex and fragment shaders by paths
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    // run program
    void Use();
};

#endif /* shader_hpp */
