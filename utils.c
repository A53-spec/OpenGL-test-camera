#include "include/glew.h"
#include "include/glfw3.h"
#include "include/linmath.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "utils.h"

char* file_read(const char* filename){
	int filesize =0;
	char* buff= NULL;
	int i;

    FILE* stream = fopen( filename, "r" );
    if(stream==NULL){
		printf("[ERROR] Error opening the %s ...\n", filename);
		abort();
	}

    fseek(stream,0,SEEK_END);
	filesize = ftell(stream);
	rewind(stream);

    buff = malloc(sizeof(char)*(filesize+1));
	if(buff==NULL){
		printf("[ERROR] Error allocating buffer for file: %s\n", filename);
		abort();
	}
	for(i=0;i<filesize;i++){//maz du buff car sinon apparition de valeurs a la fin du buffer
		buff[i] = 0;
	}

    fread(buff,1,filesize,stream);
	fclose(stream);
	buff[filesize] = '\0';//attention il faut allocate filesize+1 car sinon free crash

	return buff;
}

GLuint create_shader(const char* filename, GLenum type){
	GLint compile_ok;
	GLchar* Shader =  file_read(filename);
	if(Shader==NULL)printf("[ERROR] Error opening the file");
	printf("[INFO] Creating shaders...\n");
	GLuint res = glCreateShader(type);
	glShaderSource(res, 1, &Shader, NULL);//(const GLchar * const * string)
	glCompileShader(res);
	glGetShaderiv(res, GL_COMPILE_STATUS, &compile_ok);
	if(!compile_ok){
		switch (type){
			case 35633:
				printf("[ERROR] Error in vertex shader\n");
			break;
			case 35632:
				printf("[ERROR] Error in fragment shader\n");
			break;
			case 37305:
				printf("[ERROR] Error in compute shader\n");
			break;
			default:
				printf("[ERROR] Error in shader\n");
			break;
		}
		glDeleteShader(res);
		abort();
	}
	free(Shader);

	return res;
}

GLuint loadBMP(const char* filename){
	// Data read from the header of the BMP file
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;   // = width*height*3
	// Actual RGB data
	unsigned char* data;

	FILE* BMPptr =fopen(filename,"r");
	if(BMPptr == NULL){
		printf("[ERROR] Error opening the image file...\n");
		abort();
	}
	if(fread(header,1,54,BMPptr)!=54){
		printf("[ERROR] Not a corect BMP file. Header length not matching (!54)\n");	
		abort();
	}
	if(header[0]!='B' || header[1]!='M'){
		printf("[ERROR] Not a correct BMP file. First bytes of Header wrong (!'BM')\n");
		abort();
	}
	
	// Read ints from the byte array
	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);
	// Some BMP files are misformatted, guess missing information
	if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component			
	if (dataPos==0)      dataPos=54; // The BMP header is done that way
	// Create a buffer
	data = malloc(sizeof(unsigned char)*imageSize);
	if(data==NULL){
		printf("[ERROR] Error allocating buffer for file: %s\n", filename);
		abort();
	}
	// Read the actual data from the file into the buffer
	fread(data,1,imageSize,BMPptr);
	//Everything is in memory now, the file can be closed
	fclose(BMPptr);
	// Create one OpenGL texture
	GLuint textureID = 0;
	printf("[INFO] Creating 2D texture, id:%d\n",textureID);
	glGenTextures(1, &textureID);
	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);
	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	free(data);
	return textureID;
}

/*
GLuint loadOBJ(const char* filename, vec3* out_vertices, vec2* out_uvs, vec3* out_normals){
	unsigned int vertexIndices, uvIndices, normalIndices;
	vec3 temp_vertices;
	vec2 temp_uvs;
	vec3 temp_normals;

	FILE * file = fopen(filename, "r");
	if( file == NULL ){
		printf("[ERROR] Error opening the 3D OBJ file...\n");
		abort();
	}

	while(1){
		char lineHeader[128];
		int res = fscanf(file,"%s",lineHeader);
		if(res==EOF) break;

		if ( strcmp( lineHeader, "v" ) == 0 ){
    		vec3 vertex;
    		fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
    		temp_vertices.push_back(vertex);
		}
	}

}*/