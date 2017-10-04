#include <MDR32F9Qx_uart.h>
#include "Clock.h"
#include "Uart.h"

//  �������� ��������� �����
typedef enum {tskNoTask, tskChangeRate} UART_Task;

//  ������� ������
UART_Task ActiveTask = tskNoTask;

//	������� ��� ����� ����� ��������
const uint32_t UART_Rates[] = {9600, 56000, 115200};

//	�������� ������� ����
#define PLL_MUL  16										// = RST_CLK_CPU_PLLmul16 + 1
#define CPU_FREQ HSE_Value * PLL_MUL	// 8MHz * 16 = 128MHz

int main(void)
{
	//	������������ ����
	Clock_Init_HSE_PLL(PLL_MUL - 1);
	//	������������� UART
	UART_Initialize(UART_Rates[2]);
	UART_InitIRQ(1);
	
	while (1);
}


void UART_Handler_RX_TX(void)
{	
	uint16_t receivedData;
	
  // ��������� ���������� �� ������ ������
  if (UART_GetITStatusMasked (UART_X, UART_IT_RX) == SET)
  {
    // ����� ����������
    UART_ClearITPendingBit (UART_X, UART_IT_RX);

    // �������� ������ � �������� - ���
		receivedData = UART_ReceiveData (UART_X);
		UART_SendData (UART_X, receivedData);
		
		// ���� �������� ������ - ����� ��������
		if (ActiveTask == tskChangeRate)
		{
			ActiveTask = tskNoTask;
			
			//	���� ������ �������� � �������� ��������, �� ������ ��������
			if (receivedData < 3)
				UartSetBaud(UART_Rates[receivedData], CPU_FREQ);
		}
		
		//  ��� ��������� ������� 'R', ��������� ������ ������� ������ ����� ��������
		if (receivedData == 'R')
			ActiveTask = tskChangeRate;			
  }
	
  // ��������� ���������� �� �������� ������
  if (UART_GetITStatusMasked(UART_X, UART_IT_TX) == SET)
  {
    // ����� ����������
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
