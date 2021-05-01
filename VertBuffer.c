#include "include/glew.h"
#include "VertBuffer.h"

unsigned int  VB_Add(const float* data, unsigned int size){
    glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    return m_RendererID;
}

void VB_Destroy(unsigned int ID){
    glDeleteBuffers(1,&ID);
}

void VB_Bind(unsigned int ID){
    glBindBuffer(GL_ARRAY_BUFFER,ID);
}

void VB_Unbind(void){
    
}