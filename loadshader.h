#ifndef LOADSHADER_H
#define LOADSHADER_H

#include <glad/glad.h>

GLuint LoadShaders(const char* vertex_file_path,
                   const char* fragment_file_path);

#endif
