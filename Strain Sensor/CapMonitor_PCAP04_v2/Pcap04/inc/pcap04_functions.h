#ifndef __PCAP04_FUNCTIONS_H_
#define __PCAP04_FUNCTIONS_H_

#include "stm32l4xx_hal.h"
#include "pcap04_types.h"



void I2C_Sweep_DevAddr(uint8_t from_addr, uint8_t to_addr, uint8_t* addr_array);
void initializeI2CInf(I2C_HandleTypeDef* i2cHandler);
bool test_connection();

bool power_on();

bool uploadFirmware();
bool uploadConfiguration();
bool initializePCAP04();
bool startCDC();
bool startRDC();


#endif    //__PCAP04_FUNCTIONS_H_
