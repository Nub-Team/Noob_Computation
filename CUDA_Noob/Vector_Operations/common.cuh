#ifndef __COMMON_H__
#define __COMMON_H__

void addVectorCPU(float* a, float* b, float* c, int size);
void subtractVectorCPU(float* a, float* b, float* c, int size);
void scaleVectorCPU(float* a, float* c, float scaleFactor, int size);
bool addVectorGPU(float* a, float* b, float* c, int size);
bool subtractVectorGPU(float* a, float* b, float* c, int size);
bool scaleVectorGPU(float* a, float* c, float scaleFactor, int size);

#endif