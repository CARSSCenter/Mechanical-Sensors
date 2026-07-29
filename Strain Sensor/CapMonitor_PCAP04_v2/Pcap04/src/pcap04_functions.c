#include <stdint.h>
#include <stdbool.h>

#include "pcap04_functions.h"
#include "pcap04_defines.h"
#include "pcap04_firmwares.h"
#include "pcap04_configurations.h"


#define WR_MEM 		0xA0
#define RD_MEM 		0x20
#define WR_CONFIG 	0xA3C0	//byte wise
#define RD_CONFIG 	0x23C0	//byte wise
#define RD_RESULT 	0x40

#define POR 		0x88
#define INIT 		0x8A
#define CDC_START 	0x8C
#define RDC_START 	0x8E
#define DSP_TRIG 	0x8D
#define NV_STORE 	0x96
#define NV_RECALL 	0x99
#define NV_ERASE 	0x9C
#define TEST_READ 	0x7E

static uint8_t i2c_address = 0x50;

static I2C_HandleTypeDef* pI2CHandler = NULL;



void I2C_Sweep_DevAddr(uint8_t from_addr, uint8_t to_addr, uint8_t* addr_array)
{
	uint8_t index = 0;
	uint8_t timeout = 1;
	uint8_t trials = 3;

	for (int check_addr = from_addr; check_addr <= to_addr; check_addr++)
	{
		if (HAL_I2C_IsDeviceReady(pI2CHandler, check_addr, trials, timeout) != HAL_OK)
		{
			check_addr++;
			HAL_Delay(1);
		}
		else
		{
			addr_array[index] = check_addr;
			index++;
			break;
		}
	}
}

static HAL_StatusTypeDef I2C_Write_Opcode(uint8_t byte)
{
	HAL_StatusTypeDef status;
	uint8_t timeout = 10;
	uint8_t i2cTX[1];

	i2cTX[0] = byte;

	if (pI2CHandler == NULL)
		return HAL_ERROR;

	while (HAL_I2C_Master_Transmit(pI2CHandler, (uint16_t)i2c_address, i2cTX, 1, timeout) != HAL_OK)
	{
		if (HAL_I2C_GetError(pI2CHandler) != HAL_I2C_ERROR_AF)
		{
			I2CError_Handler();
		}
	}

	while (HAL_I2C_GetState(pI2CHandler) != HAL_I2C_STATE_READY);

	return HAL_OK;
}

static HAL_StatusTypeDef I2C_Memory_Access(uint8_t opcode, uint16_t address, uint8_t* byte, uint16_t size)
{
	float savety_factor = 1.2e3;
	uint32_t timeout = ((1/100e3) * (2 + size) * 9) * savety_factor;

	if (WR_MEM == opcode)
	{
		uint8_t i2cTX[size + 2];

		i2cTX[0] = opcode | (uint8_t)(address>>8);
		i2cTX[1] = (uint8_t)address;

		for (int i = 0; i < size; i++)
		{
			i2cTX[2 + i] = byte[i];
		}

		while (HAL_I2C_Master_Transmit(pI2CHandler, (uint16_t)i2c_address, i2cTX, (2+size), timeout) != HAL_OK)
		{
			if (HAL_I2C_GetError(pI2CHandler) != HAL_I2C_ERROR_AF)
			{
				Error_Handler();
			}
		}

		while (HAL_I2C_GetState(pI2CHandler) != HAL_I2C_STATE_READY);
	}
	else
	{
		uint8_t i2cTX[2];
		uint8_t i2cRX[size];

		i2cTX[0] = opcode | (uint8_t)(address>>8);
		i2cTX[1] = address;

		while (HAL_I2C_Master_Transmit(pI2CHandler, (uint16_t)i2c_address, i2cTX, 2, timeout) != HAL_OK)
		{
			if (HAL_I2C_GetError(pI2CHandler) != HAL_I2C_ERROR_AF)
			{
				Error_Handler();
			}
		}
		while (HAL_I2C_GetState(pI2CHandler) != HAL_I2C_STATE_READY);

		while (HAL_I2C_Master_Receive(pI2CHandler, i2c_address, i2cRX, size, timeout) != HAL_OK)
		{
			if (HAL_I2C_GetError(pI2CHandler) != HAL_I2C_ERROR_AF)
			{
				Error_Handler();
			}
		}
		while (HAL_I2C_GetState(pI2CHandler) != HAL_I2C_STATE_READY);

		for (int i = 0; i < size; i++)
		{
			byte[i] = i2cRX[i];
		}
	}

	return HAL_OK;
}

static HAL_StatusTypeDef I2C_Config_Access(uint32_t opcode, uint8_t address, uint8_t *byte, uint8_t size)
{
	uint8_t timeout = 100;
	uint8_t i2cTX[256];
	uint8_t i2cRX[256];

	i2cTX[0] = (uint8_t)(opcode>>8);
	i2cTX[1] = address | (uint8_t)opcode;

	if (WR_CONFIG == opcode)
	{
		if (size == 1)
		{
			i2cTX[2] = byte[0];
		}
		else
		{
			for (int i = 0; i < size; i++)
			{
				i2cTX[2 + i] = byte[i];
			}
		}

		while (HAL_I2C_Master_Transmit(pI2CHandler, i2c_address, i2cTX, (2 + size), timeout) != HAL_OK)
		{
			if (HAL_I2C_GetError(pI2CHandler) != HAL_I2C_ERROR_AF)
			{
				Error_Handler();
			}
		}
		while (HAL_I2C_GetState(pI2CHandler) != HAL_I2C_STATE_READY);
	}
	else
	{
		while (HAL_I2C_Master_Transmit(pI2CHandler, i2c_address, i2cTX, 2, timeout) != HAL_OK)
		{
			if (HAL_I2C_GetError(pI2CHandler) != HAL_I2C_ERROR_AF)
			{
				Error_Handler();
			}
		}
		while (HAL_I2C_GetState(pI2CHandler) != HAL_I2C_STATE_READY);

		while (HAL_I2C_Master_Receive(pI2CHandler, i2c_address, i2cRX, size, timeout) != HAL_OK)
		{
			if (HAL_I2C_GetError(pI2CHandler) != HAL_I2C_ERROR_AF)
			{
				Error_Handler();
			}
		}
		while (HAL_I2C_GetState(pI2CHandler) != HAL_I2C_STATE_READY);

		for (int i = 0; i < size; i++)
		{
			byte[i] = i2cRX[i];
		}
	}

	return HAL_OK;

}

void initializeI2CInf(I2C_HandleTypeDef* i2cHandler)
{
	pI2CHandler = i2cHandler;
}

bool test_connection()
{
	bool bRet = false;
	HAL_StatusTypeDef ret = HAL_OK;
	uint8_t buf;
	uint8_t retByte = 0xAA;

	uart_printf("\r\n\tSend I2C TEST_READ to device (addr=0x%02x)\r\n", i2c_address);
	ret = I2C_Write_Opcode(TEST_READ);
	ret = HAL_I2C_Master_Receive(pI2CHandler, i2c_address, &buf, 1, 1);

	uart_printf("\r\n\tReceived: 0x%02x...", buf);

	switch (buf)
	{
		case 0x11:
		{
			ret = true;
			uart_printf("\t Expected.\r\n");
			break;
		}
		case 0x88:
		{
			ret = false;
			uart_printf("\t Not Expected: There is a bit/little-endian swap.\r\n");
			break;
		}
		case 0xee:
		{
			ret = false;
			uart_printf("\t Not Expected: During read cycle all bits are inverted.\r\n");
			break;
		}
		case 0x77:
		{
			ret = false;
			uart_printf("\t Not Expected: Inverted bits and bit/little-endian swap.\r\n");
			break;
		}
		default:
		{
			ret = false;
			uart_printf("\t Not Expected: Unknown.\r\n");
			break;
		}
	}
	return ret;
}

bool power_on()
{
	HAL_StatusTypeDef hRet = HAL_ERROR;

	hRet = I2C_Write_Opcode(POR);

	HAL_Delay(500);

	return (HAL_OK == hRet) ? true : false;

}

bool initializePCAP04()
{
	HAL_StatusTypeDef hRet = HAL_ERROR;

	hRet = I2C_Write_Opcode(INIT);

	HAL_Delay(500);

	return (HAL_OK == hRet) ? true : false;

}

bool startCDC()
{
	HAL_StatusTypeDef hRet = HAL_ERROR;

	hRet = I2C_Write_Opcode(CDC_START);

	return (HAL_OK == hRet) ? true : false;
}


bool startRDC()
{
	HAL_StatusTypeDef hRet = HAL_ERROR;

	hRet = I2C_Write_Opcode(RDC_START);

	return (HAL_OK == hRet) ? true : false;
}

void I2CError_Handler()
{
	__disable_irq();
	while(1)
	{
		uart_printf("I2CError\r\n");
		HAL_Delay(10);
	}
}


bool uploadFirmware()
{
	uint8_t checkBuf[100] = {0x00};
	HAL_StatusTypeDef hRet = HAL_ERROR;

	hRet = I2C_Memory_Access(WR_MEM, 0x00, PCap04v1_standard_v1, sizeof(PCap04v1_standard_v1));

	if (HAL_OK != hRet)
	{
		return false;
	}

	hRet = I2C_Memory_Access(RD_MEM, 0x00, checkBuf, sizeof(checkBuf));
	if (HAL_OK != hRet)
	{
		return false;
	}

	for (int i = 0; i < sizeof(checkBuf); i++)
	{
		if (checkBuf[i] != PCap04v1_standard_v1[i])
		{
			return false;
		}
	}


	return true;
}

bool getResult(pcap04_result_t* res)
{
	HAL_StatusTypeDef hRet = HAL_ERROR;
	uint8_t timeout = 10;
	uint8_t i2cTX[1];
	uint8_t i2cRX[4];

	uint32_t temp_u32 = 0;

	i2cTX[0] = 0x40;

	hRet = HAL_I2C_Master_Transmit(pI2CHandler, i2c_address, i2cTX, 1, timeout);
	if (HAL_OK != hRet)
	{
		return false;
	}
	hRet = HAL_I2C_Master_Receive(pI2CHandler, i2c_address, i2cRX, 4, timeout);
	if (HAL_OK != hRet)
	{
		return false;
	}

	res->res0 = (i2cRX[3]<<24) + (i2cRX[2]<<16) + (i2cRX[1]<<8) + (i2cRX[0]);

	i2cTX[0] = 0x44;

	hRet = HAL_I2C_Master_Transmit(pI2CHandler, i2c_address, i2cTX, 1, timeout);
	if (HAL_OK != hRet)
	{
		return false;
	}
	hRet = HAL_I2C_Master_Receive(pI2CHandler, i2c_address, i2cRX, 4, timeout);
	if (HAL_OK != hRet)
	{
		return false;
	}

	res->res1 = (i2cRX[3]<<24) + (i2cRX[2]<<16) + (i2cRX[1]<<8) + (i2cRX[0]);

	i2cTX[0] = 0x48;

	hRet = HAL_I2C_Master_Transmit(pI2CHandler, i2c_address, i2cTX, 1, timeout);
	if (HAL_OK != hRet)
	{
		return false;
	}
	hRet = HAL_I2C_Master_Receive(pI2CHandler, i2c_address, i2cRX, 4, timeout);
	if (HAL_OK != hRet)
	{
		return false;
	}

	res->res2 = (i2cRX[3]<<24) + (i2cRX[2]<<16) + (i2cRX[1]<<8) + (i2cRX[0]);


	return true;
}

bool uploadConfiguration()
{
	uint8_t checkBuf[64] = {0x00};
	HAL_StatusTypeDef hRet = HAL_ERROR;

	hRet = I2C_Config_Access(WR_CONFIG, 0x00, PCap04v1_standard_v1_configuration, sizeof(PCap04v1_standard_v1_configuration));
	if (HAL_OK != hRet)
	{
		return false;
	}

	hRet = I2C_Config_Access(RD_CONFIG, 0x00, checkBuf, sizeof(checkBuf));
	if (HAL_OK != hRet)
	{
		return false;
	}

	for (int i = 0; i < sizeof(checkBuf); i++)
	{
		if (checkBuf[i] != PCap04v1_standard_v1_configuration[i])
		{
			return false;
		}
	}


	return true;
}


