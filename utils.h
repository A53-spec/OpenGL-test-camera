#ifndef UTILS_SHADER_H_INCLUDED
#define UTILS_SHADER_H_INCLUDED

typedef struct vector3{
    float x;
    float y;
    float z;
}vector3;

typedef struct vector2{
    float x;
    float y;
}vector2;

char* file_read(const char* filename);
GLuint create_shader(const char* filename, GLenum type);
GLuint loadBMP(const char* filename);
GLuint loadOBJ(const char* filename);
#endif 



