#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>

char* readFile(const char* path)
{
    FILE* file = fopen(path, "rb");

    if (!file) {
        printf("Impossible to open %s\n", path);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char* buffer = malloc(size + 1);

    if (!buffer) {
        fclose(file);
        return NULL;
    }

    size_t bytesRead = fread(buffer, 1, size, file);

    if (bytesRead != size) {
        fclose(file);
        free(buffer);
        return NULL;
    }

    buffer[size] = '\0';

    fclose(file);
    return buffer;
}

GLuint LoadShaders(const char* vertex_file_path,
                   const char* fragment_file_path)
{
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    char* VertexShaderCode = readFile(vertex_file_path);
    char* FragmentShaderCode = readFile(fragment_file_path);

    if (!VertexShaderCode || !FragmentShaderCode) {
        free(VertexShaderCode);
        free(FragmentShaderCode);
        return 0;
    }

    GLint Result = GL_FALSE;
    GLint InfoLogLength;

    printf("Compiling shader : %s\n", vertex_file_path);

    glShaderSource(VertexShaderID, 1,
                   (const GLchar* const*)&VertexShaderCode,
                   NULL);

    glCompileShader(VertexShaderID);

    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

    if (InfoLogLength > 0) {
        char* errorMessage = malloc(InfoLogLength + 1);

        glGetShaderInfoLog(VertexShaderID,
                           InfoLogLength,
                           NULL,
                           errorMessage);

        printf("%s\n", errorMessage);

        free(errorMessage);
    }

    printf("Compiling shader : %s\n", fragment_file_path);

    glShaderSource(FragmentShaderID, 1,
                   (const GLchar* const*)&FragmentShaderCode,
                   NULL);

    glCompileShader(FragmentShaderID);

    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

    if (InfoLogLength > 0) {
        char* errorMessage = malloc(InfoLogLength + 1);

        glGetShaderInfoLog(FragmentShaderID,
                           InfoLogLength,
                           NULL,
                           errorMessage);

        printf("%s\n", errorMessage);

        free(errorMessage);
    }

    printf("Linking program\n");

    GLuint ProgramID = glCreateProgram();

    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);

    glLinkProgram(ProgramID);

    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);

    if (InfoLogLength > 0) {
        char* errorMessage = malloc(InfoLogLength + 1);

        glGetProgramInfoLog(ProgramID,
                            InfoLogLength,
                            NULL,
                            errorMessage);

        printf("%s\n", errorMessage);

        free(errorMessage);
    }

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    free(VertexShaderCode);
    free(FragmentShaderCode);

    return ProgramID;
}
