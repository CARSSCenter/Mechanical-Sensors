#ifndef __UART_PRINTF_H_
#define __UART_PRINTF_H_

#include "stm32l4xx_hal.h"
#include <stdarg.h>
#include <stdint.h>

void UART_Printf_Init(UART_HandleTypeDef* huart);
void uart_printf(const uint8_t* format, ...);

#endif    //__UART_PRINTF_H_
