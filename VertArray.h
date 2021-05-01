#ifndef VERTARRAY_H_INCLUDED
#define VERTARRAY_H_INCLUDED

unsigned int m_RendererID;

unsigned int VA_Add(const float* data, unsigned int size);
void VA_Destroy(unsigned int ID);
void VA_Bind(unsigned int ID);
void VA_Unbind(void);

#endif 



