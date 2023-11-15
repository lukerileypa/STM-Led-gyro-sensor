#include <LIS3DSH.h>
#include "main.h"
extern SPI_HandleTypeDef hspi1;
void LIS3DSH_Init(void){

	HAL_StatusTypeDef res;

	uint8_t TxBuf[10] = {0};

	TxBuf[0] = 0x20 | 0x00; // Address | W/R bit
	TxBuf[1] = 0x67; // Data to be written to slave memory (0b01100111)

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET); // Set SPI CS low
	res = HAL_SPI_Transmit(&hspi1, TxBuf, 2, 100); // Send address + 1 byte data
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET); // Set SPI CS high



}
void LIS3DSH_ReadXYZ(int16_t *pData){

	HAL_StatusTypeDef res;

	uint8_t TxBuf[10] = {0};
	uint8_t RxBuf[10] = {0};

	TxBuf[0] = 0x28 | 0x80; // Address | W/R bit

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET); // Set SPI CS low
	res = HAL_SPI_Transmit(&hspi1, TxBuf, 1, 100); // Send address
	res = HAL_SPI_Receive(&hspi1, RxBuf, 6, 100); //Receive 6 byteS
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET); // Set SPI CS high

	pData[0] = *((int16_t*) (RxBuf)); //pData[0] is RxBuf[0] and RxBuf[1], raw x acceleration
	pData[1] = *((int16_t*) (RxBuf+2)); //pData[1] is RxBuf[2] and RxBuf[3], raw y acceleration
	pData[2] = *((int16_t*) (RxBuf+4)); //pData[2] is RxBuf[4] and RxBuf[5], raw z acceleration
	}
