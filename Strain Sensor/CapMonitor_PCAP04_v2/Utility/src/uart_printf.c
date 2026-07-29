#include "uart_printf.h"
#include <string.h>

#define PRINTF_BUFFER_SIZE		1000

static UART_HandleTypeDef* uart_handle = NULL;
static uint8_t printf_buffer[PRINTF_BUFFER_SIZE];

void UART_Printf_Init(UART_HandleTypeDef* huart)
{
	uart_handle = huart;
}

static void uart_transmit_string(const uint8_t* str)
{
	if (uart_handle == NULL)
	{
		return;
	}

	HAL_UART_Transmit(uart_handle, str, strlen((const char*)str), HAL_MAX_DELAY);
}

void uart_printf(const uint8_t* format, ...)
{
	if (uart_handle == NULL)
	{
		return;
	}

	va_list args;
	va_start(args, format);

	vsnprintf((char*)printf_buffer, PRINTF_BUFFER_SIZE, (const char*)format, args);

	va_end(args);

	uart_transmit_string(printf_buffer);
}
