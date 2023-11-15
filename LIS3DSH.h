#ifndef LIS3DSH
#define LIS3DSH
#include <stdint.h>
void LIS3DSH_Init(void);
void LIS3DSH_ReadXYZ(int16_t* pData);
#endif
