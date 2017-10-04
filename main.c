#include <MDR32F9Qx_uart.h>
#include "Clock.h"
#include "Uart.h"

//  Перечень возможных задач
typedef enum {tskNoTask, tskChangeRate} UART_Task;

//  Текущая задача
UART_Task ActiveTask = tskNoTask;

//	Частоты для теста смена скорости
const uint32_t UART_Rates[] = {9600, 56000, 115200};

//	Тактовая частота ядра
#define PLL_MUL  16										// = RST_CLK_CPU_PLLmul16 + 1
#define CPU_FREQ HSE_Value * PLL_MUL	// 8MHz * 16 = 128MHz

int main(void)
{
	//	Тактирование ядра
	Clock_Init_HSE_PLL(PLL_MUL - 1);
	//	Инициализация UART
	UART_Initialize(UART_Rates[2]);
	UART_InitIRQ(1);
	
	while (1);
}


void UART_Handler_RX_TX(void)
{	
	uint16_t receivedData;
	
  // Обработка прерывания по Приему данных
  if (UART_GetITStatusMasked (UART_X, UART_IT_RX) == SET)
  {
    // Сброс прерывания
    UART_ClearITPendingBit (UART_X, UART_IT_RX);

    // Получаем данные и отвечаем - ЭХО
		receivedData = UART_ReceiveData (UART_X);
		UART_SendData (UART_X, receivedData);
		
		// Если активная задача - смена скорости
		if (ActiveTask == tskChangeRate)
		{
			ActiveTask = tskNoTask;
			
			//	Если индекс скорости в заданных пределах, то меняем скорость
			if (receivedData < 3)
				UartSetBaud(UART_Rates[receivedData], CPU_FREQ);
		}
		
		//  При получении символа 'R', следующим байтом ожидаем индекс новой скорости
		if (receivedData == 'R')
			ActiveTask = tskChangeRate;			
  }
	
  // Обработка прерывания от Передачи данных
  if (UART_GetITStatusMasked(UART_X, UART_IT_TX) == SET)
  {
    // Сброс прерывания
    UART_ClearITPendingBit (UART_X, UART_IT_TX);
  }	
}

void UART1_IRQHandler (void)
{
	UART_Handler_RX_TX();
}

void UART2_IRQHandler (void)
{
	UART_Handler_RX_TX();
}
