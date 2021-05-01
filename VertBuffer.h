#ifndef VERTBUFFER_H_INCLUDED
#define VERTBUFFER_H_INCLUDED

unsigned int m_RendererID;

unsigned int VB_Add(const float* data, unsigned int size);
void VB_Destroy(unsigned int ID);
void VB_Bind(unsigned int ID);
void VB_Unbind(void);

#endif 



